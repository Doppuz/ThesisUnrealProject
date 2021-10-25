// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeManager.h"
#include "Containers/Array.h"
#include "DrawDebugHelpers.h"
#include "MazeCell2.h"
#include "Kismet/GameplayStatics.h"
#include "../Elements/Maze/Maze.h"
#include "../Elements/GeneralElements/Doors/Door.h"
#include "../Elements/GeneralElements/Doors/DoorKiller.h"
#include "../Elements/GeneralElements/Doors/DoorRiddle.h"
#include "../Elements/GeneralElements/Doors/DoorAchiever.h"
#include "../Elements/GeneralElements/Doors/DoorExplorer.h"
#include "../Elements/GeneralElements/CoinController.h"
#include "../Elements/GeneralElements/Heart.h"
#include "../Elements/Room/RoomKiller.h"
#include "../Elements/Room/RoomAchiever.h"
#include "../Elements/Room/RoomSocializer.h"
#include "../Elements/Triggers/Trigger.h"
#include "../Elements/Triggers/TriggerSpawnNight.h"
#include "../Character/EnemyAI/AIBull.h"
#include "../Character/EnemyAI/AIShooterPawn.h"
#include "../Character/EnemyAI/PatrolAI2.h"
#include "../Character/AllyAI/PawnInteractiveClass.h"
#include "../Character/CharacterPawnQuad.h"
#include "../Character/AllyAI/PawnInteractiveMove.h"
#include "../Character/AllyAI/RiddleNPC.h"
#include "../Elements/GeneralElements/GeneralElem.h"
#include "../Elements/Platforms/ShakingFallenPlatform.h"
#include "../Elements/Portal/Portal.h"
#include "../Elements/Portal/PortalNight.h"
#include "../Elements/Puzzle/PuzzleButton.h"
#include "../Elements/Puzzle/PuzzleButtonPortal.h"
#include "MazeTypes/SocializerMaze.h"
#include "../Elements/Destructible/DestructibleElements.h"
#include "../Elements/Statue/StatueInteractElem.h"
#include "../Obstacle/Trap.h"
#include "../Elements/Destructible/GenericDestructibleElements.h"
#include "../Elements/Triggers/TriggerSpawnAlly.h"
#include "../Elements/Hat/Hat.h"
#include "../CheckPoints/CheckPointLevel1.h"
#include "../CheckPoints/SaveGameLevel1.h"
#include "../CheckPoints/SaveGameBartle.h"
#include "EngineUtils.h"
#include "../Elements/Light/CeilingLight.h"
#include "../Elements/Storm/Storm.h"
#include "../Elements/FinalLevelActor.h"
#include "../GameModeAbstract.h"
#include "../AdaptiveExperience.h"

// Sets default values
AMazeManager::AMazeManager(){

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    this->Distance = 770.f; //770
    
}

AMazeManager::~AMazeManager() {
    
    delete MazeGraph;

    for(Graph<TArray<AMazeCell2*>> G : OtherPaths){

        for(TArray<AMazeCell2*>* N : G.GetNodes())
            
            delete N;

    }


}

#pragma region MazeManager

// Called when the game starts or when spawned
void AMazeManager::BeginPlay(){
    
	Super::BeginPlay();

	AGameModeAbstract* GameMode = Cast<AGameModeAbstract>(GetWorld()->GetAuthGameMode());

    if (USaveGameBartle* LoadedGame = Cast<USaveGameBartle>(UGameplayStatics::LoadGameFromSlot("Bartle", 0))){

        UE_LOG(LogTemp,Warning,TEXT("Values = %f, %f, %f, %f"),  LoadedGame->Achiever, LoadedGame->Killer, LoadedGame->Explorer, LoadedGame->Socializer);

        GameMode->Update->Types.Add(Type::Achiever, LoadedGame->Achiever);
        GameMode->Update->Types.Add(Type::Killer, LoadedGame->Killer);
        GameMode->Update->Types.Add(Type::Explorer, LoadedGame->Explorer);
        GameMode->Update->Types.Add(Type::Socializer, LoadedGame->Socializer);

    }

    if (USaveGameLevel1* LoadedGame = Cast<USaveGameLevel1>(UGameplayStatics::LoadGameFromSlot("CheckpointLevel1", 0))){
        
        //Load Speech
        Speech = ConvertSpeechBack(LoadedGame->Speech);
        Questions = ConvertSpeechBack(LoadedGame->Questions);
        BlockedSpeech = ConvertSpeechBack(LoadedGame->BlockedSpeech);
        OldSpeech = ConvertSpeechBack(LoadedGame->OldSpeech);
        OldQuestions = ConvertSpeechBack(LoadedGame->OldQuestions);
        OldBlockedSpeech = ConvertSpeechBack(LoadedGame->OldBlockedSpeech);

        //Load Maze Actors.
        for(int i = 0; i < LoadedGame->MazeTransformMap.Num(); i++){
            
            if(LoadedGame->MazeTransformMap[i].TransformsFloor.Num() < 1){
                
                AMaze* Maze = GetWorld()->SpawnActor<AMaze>(MazeActorClass,LoadedGame->MazeTransformMap[i].Position,FRotator::ZeroRotator);
                Maze->FloorInstances->AddInstances(LoadedGame->MazeTransformMap[i].TransformsFloor,false);
                Maze->WallInstances->AddInstances(LoadedGame->MazeTransformMap[i].TransformsWall,false);
                Maze->ObstacleInstances->AddInstances(LoadedGame->MazeTransformMap[i].TransformsObstacle,false);
        
            }else{

                AMaze* MazeFloor = GetWorld()->SpawnActor<AMaze>(MazeActorClass,LoadedGame->MazeTransformMap[i].Position,FRotator::ZeroRotator);
                MazeFloor->FloorInstances->AddInstances(LoadedGame->MazeTransformMap[i].TransformsFloor,false);
                MazeFloor->MetalCrateInstances->AddInstances(LoadedGame->MazeTransformMap[i].TransformsMetalCrate,false);       
                UGameplayStatics::GetPlayerPawn(GetWorld(),0)->MoveIgnoreActorAdd(MazeFloor);
            
            }
        }

        //Load Destructible Elems
        for(int i = 0; i < LoadedGame->DestructibleElem.Num(); i++){
            
            AGenericDestructibleElements* Elem = GetWorld()->SpawnActor<AGenericDestructibleElements>(
                LoadedGame->DestructibleElem[i].ActorClass,
                LoadedGame->DestructibleElem[i].Transform);

            Elem->ID = LoadedGame->DestructibleElem[i].ID;
            Elem->SpawnActor = LoadedGame->DestructibleElem[i].SpawnActor;

        }

        //Load Coins
        for(int i = 0; i < LoadedGame->CoinElem.Num(); i++){
            
            ACoinController* Elem = GetWorld()->SpawnActor<ACoinController>(
                LoadedGame->CoinElem[i].ActorClass,
                LoadedGame->CoinElem[i].Transform);

        }
        
        //Load Hats
        for(int i = 0; i < LoadedGame->HatElem.Num(); i++){
            
            AHat* Elem = GetWorld()->SpawnActor<AHat>(
                LoadedGame->HatElem[i].ActorClass,
                LoadedGame->HatElem[i].Transform);

        }

        //Load Trap
        for(int i = 0; i < LoadedGame->TrapElem.Num(); i++){
            
            ATrap* Elem = GetWorld()->SpawnActor<ATrap>(
                LoadedGame->TrapElem[i].ActorClass,
                LoadedGame->TrapElem[i].Transform);

        }

        //Load Heart
        for(int i = 0; i < LoadedGame->HeartElem.Num(); i++){
            
            AHeart* Elem = GetWorld()->SpawnActor<AHeart>(
                LoadedGame->HeartElem[i].ActorClass,
                LoadedGame->HeartElem[i].Transform);

        }
        
        //Load Fallen Plat
        for(int i = 0; i < LoadedGame->FallenPlatformElem.Num(); i++){
            
            AShakingFallenPlatform* Elem = GetWorld()->SpawnActor<AShakingFallenPlatform>(
                LoadedGame->FallenPlatformElem[i].ActorClass,
                LoadedGame->FallenPlatformElem[i].Transform);

        }

        //Load Enemies
        for(int i = 0; i < LoadedGame->Enemies.Num(); i++){
            
            AEnemyAIAbstract* Elem = GetWorld()->SpawnActor<AEnemyAIAbstract>(
                LoadedGame->Enemies[i].ActorClass,
                LoadedGame->Enemies[i].Transform);

            Elem->IDEnemy = LoadedGame->Enemies[i].ID;

        }

        //Load Allies
        for(int i = 0; i < LoadedGame->Allies.Num(); i++){
            
            APawnInteractiveClass* Elem = GetWorld()->SpawnActor<APawnInteractiveClass>(
                LoadedGame->Allies[i].ActorClass,
                LoadedGame->Allies[i].Transform);

            Elem->Speech = LoadedGame->Allies[i].Speech;
            Elem->QuestionAt = LoadedGame->Allies[i].QuestionAt;
            Elem->bAlreadySpoken = LoadedGame->Allies[i].bAlreadySpoken;
            Elem->ID = LoadedGame->Allies[i].ID;

        }
        
        //Load Patrols
        for(int i = 0; i < LoadedGame->Patrols.Num(); i++){
            
            APatrolAI2* Elem = GetWorld()->SpawnActorDeferred<APatrolAI2>(
                LoadedGame->Patrols[i].ActorClass,
                LoadedGame->Patrols[i].Transform);

            Elem->Positions = LoadedGame->Patrols[i].Positions;
            Elem->StartIndex = LoadedGame->Patrols[i].StartIndex;
            Elem->StartDirection = LoadedGame->Patrols[i].StartDirection;
            
            Elem->FinishSpawning(LoadedGame->Patrols[i].Transform);

        }

        //Load Move Allies
        for(int i = 0; i < LoadedGame->MoveAllies.Num(); i++){
            
            APawnInteractiveMove* Elem = GetWorld()->SpawnActorDeferred<APawnInteractiveMove>(
                LoadedGame->MoveAllies[i].ActorClass,
                LoadedGame->MoveAllies[i].Transform);

            Elem->Positions = LoadedGame->MoveAllies[i].Positions;
            
            Elem->FinishSpawning(LoadedGame->MoveAllies[i].Transform);

            Elem->Speech = LoadedGame->MoveAllies[i].Speech;
            Elem->QuestionAt = LoadedGame->MoveAllies[i].QuestionAt;
            Elem->bAlreadySpoken = LoadedGame->MoveAllies[i].bAlreadySpoken;
        }

        //Load Door
        for(int i = 0; i < LoadedGame->Doors.Num(); i++){

            ADoor* Elem = GetWorld()->SpawnActorDeferred<ADoor>(DoorClass,LoadedGame->Doors[i].Transform);
            Elem->bOpenDoor = LoadedGame->Doors[i].bOpenDoor;
            Elem->FinalPosition = LoadedGame->Doors[i].FinalPosition;
            Elem->FinishSpawning(LoadedGame->Doors[i].Transform);

            Elem->ID = LoadedGame->Doors[i].ID;

        }

        //Load Door Riddle
        for(int i = 0; i < LoadedGame->DoorsRiddle.Num(); i++){

            ADoorRiddle* Elem = GetWorld()->SpawnActorDeferred<ADoorRiddle>(DoorRiddleClass,LoadedGame->DoorsRiddle[i].Transform);
            Elem->Speech = &Speech;
            Elem->OldSpeech = &OldSpeech;
            Elem->Questions = &Questions;
            Elem->OldQuestions = &OldQuestions;
            Elem->bOpenDoor = LoadedGame->DoorsRiddle[i].bOpenDoor;
            Elem->FinalPosition = LoadedGame->DoorsRiddle[i].FinalPosition;
            Elem->FinishSpawning(LoadedGame->DoorsRiddle[i].Transform);
            
            Elem->ID = LoadedGame->DoorsRiddle[i].ID;

        }

        //Load Door Explorer
        for(int i = 0; i < LoadedGame->DoorsExplorer.Num(); i++){

            ADoorExplorer* Elem = GetWorld()->SpawnActorDeferred<ADoorExplorer>(DoorExplorerClass,LoadedGame->DoorsExplorer[i].Transform);
            Elem->bOpenDoor = LoadedGame->DoorsExplorer[i].bOpenDoor;
            Elem->FinalPosition = LoadedGame->DoorsExplorer[i].FinalPosition;
            Elem->FinishSpawning(LoadedGame->DoorsExplorer[i].Transform);
            
            Elem->ID = LoadedGame->DoorsExplorer[i].ID;
        }

        //Load Door Achiever
        for(int i = 0; i < LoadedGame->DoorsAchiever.Num(); i++){

            ADoorAchiever* Elem = GetWorld()->SpawnActorDeferred<ADoorAchiever>(DoorAchieverClass,LoadedGame->DoorsAchiever[i].Transform);
            Elem->bCheckpoint = true;
            Elem->bOpenDoor = LoadedGame->DoorsAchiever[i].bOpenDoor;
            Elem->FinalPosition = LoadedGame->DoorsAchiever[i].FinalPosition;
            Elem->KeyPosition = LoadedGame->DoorsAchiever[i].KeyPos;
            Elem->FinishSpawning(LoadedGame->DoorsAchiever[i].Transform);
            Elem->ID = LoadedGame->DoorsAchiever[i].ID;

            for(int j = 0; j < LoadedGame->DoorsAchiever[i].IDs.Num(); j++){
                
                for (TActorIterator<AGenericDestructibleElements> ActorItr(GetWorld()); ActorItr; ++ActorItr){
                    
                    if((*ActorItr)->ID == LoadedGame->DoorsAchiever[i].IDs[j]){
                        
                        Elem->DestrActors.Add((*ActorItr));
                        
                        if((*ActorItr)->ID == LoadedGame->DoorsAchiever[i].IDKey)
                            (*ActorItr)->DestrDelegate.AddDynamic(Elem, &ADoorAchiever::SpawnKey);
                        
                        break;

                    }

                }

            }

        }

        //Load Door Killer
        for(int i = 0; i < LoadedGame->DoorsKiller.Num(); i++){

            ADoorKiller* Elem = GetWorld()->SpawnActorDeferred<ADoorKiller>(DoorKillerClass,LoadedGame->DoorsKiller[i].Transform);
            Elem->bOpenDoor =  LoadedGame->DoorsKiller[i].bOpenDoor;
            Elem->FinalPosition = LoadedGame->DoorsKiller[i].FinalPosition;
            Elem->FinishSpawning(LoadedGame->DoorsKiller[i].Transform);
            Elem->ID = LoadedGame->DoorsKiller[i].ID;

            for(int j = 0; j < LoadedGame->DoorsKiller[i].IDs.Num(); j++){
                
                for (TActorIterator<AEnemyAIAbstract> ActorItr(GetWorld()); ActorItr; ++ActorItr){
                    
                    if((*ActorItr)->IDEnemy == LoadedGame->DoorsKiller[i].IDs[j]){
                        (*ActorItr)->Destroy();
                        break;
                    }

                }

            }

        }

        //Load Checkpoints
        for(int i = 0; i < LoadedGame->Checkpoints.Num(); i++){
            
            ACheckPointLevel1* Elem = GetWorld()->SpawnActor<ACheckPointLevel1>(
                LoadedGame->Checkpoints[i].ActorClass,
                LoadedGame->Checkpoints[i].Transform);

            Elem->MazeManager = this;

        }

        //Load LastActor
        if(LoadedGame->LastActor.ActorClass != nullptr)
            
            GetWorld()->SpawnActor<AFinalLevelActor>(
                LoadedGame->LastActor.ActorClass,
                LoadedGame->LastActor.Transform);


        //Load Storms
        for(int i = 0; i < LoadedGame->Storms.Num(); i++){
            
            AStorm* Elem = GetWorld()->SpawnActorDeferred<AStorm>(
                LoadedGame->Storms[i].ActorClass,
                LoadedGame->Storms[i].Transform);

                
            Elem->Positions = LoadedGame->Storms[i].Positions;

            Elem->FinishSpawning(LoadedGame->Storms[i].Transform);

        }

        //Load Lights
       /*for(int i = 0; i < LoadedGame->Lights.Num(); i++){
            
            ACeilingLight* Elem = GetWorld()->SpawnActor<ACeilingLight>(
                LoadedGame->Lights[i].ActorClass,
                LoadedGame->Lights[i].Transform);

        }*/

        //Load Night portals
        for(int i = 0; i < LoadedGame->NightPortals.Num(); i++){
            
            APortal* Elem = GetWorld()->SpawnActor<APortal>(
                LoadedGame->NightPortals[i].ActorClass,
                LoadedGame->NightPortals[i].Transform);

            Elem->NewPosition = LoadedGame->NightPortals[i].NewPosition;

        }

        //Load Puzzle portals
        for(int i = 0; i < LoadedGame->PuzzlePortals.Num(); i++){
            
            APuzzleButtonPortal* Elem = GetWorld()->SpawnActorDeferred<APuzzleButtonPortal>(
                LoadedGame->PuzzlePortals[i].ActorClass,
                LoadedGame->PuzzlePortals[i].Transform);

            Elem->EndSpawnPosition = LoadedGame->PuzzlePortals[i].EndSpawnPosition;

            for (TActorIterator<ADoor> ActorItr(GetWorld()); ActorItr; ++ActorItr){
                    
                if((*ActorItr)->ID == LoadedGame->PuzzlePortals[i].DoorID){
                    Elem->Door = (*ActorItr);
                    break;
                }

            }

            for (TActorIterator<APortalNight> ActorItr(GetWorld()); ActorItr; ++ActorItr){

                Elem->StartPortal = (*ActorItr);

            }

            Elem->FinishSpawning(LoadedGame->PuzzlePortals[i].Transform);

        }

        //Load Room Killer / Socializer
        if(LoadedGame->RoomKillerStruct.ActorClass != nullptr){

            ARoomKiller* Elem = GetWorld()->SpawnActorDeferred<ARoomKiller>(
                LoadedGame->RoomKillerStruct.ActorClass,
                LoadedGame->RoomKillerStruct.Transform);

            Elem->StartPortalPos = LoadedGame->RoomKillerStruct.StartPortalPos;

            for (TActorIterator<ADoor> ActorItr(GetWorld()); ActorItr; ++ActorItr){
                        
                if((*ActorItr)->ID == LoadedGame->RoomKillerStruct.DoorID){
                    Elem->Door = (*ActorItr);
                    break;
                }

            }

            for (TActorIterator<APawnInteractiveClass> ActorItr(GetWorld()); ActorItr; ++ActorItr){
                        
                if(!(*ActorItr)->IsA(APawnInteractiveMove::StaticClass()) && !(*ActorItr)->IsA(ARiddleNPC::StaticClass()) &&
                    (*ActorItr)->ID == LoadedGame->RoomKillerStruct.NPCID){
                    
                    (*ActorItr)->Destroy();
                    break;

                }

            }

            Elem->FinishSpawning(LoadedGame->RoomKillerStruct.Transform);

        }

        //Load Room Achiever
        if(LoadedGame->RoomAchieverStruct.ActorClass != nullptr){

            ARoomAchiever* Elem = GetWorld()->SpawnActorDeferred<ARoomAchiever>(
                LoadedGame->RoomAchieverStruct.ActorClass,
                LoadedGame->RoomAchieverStruct.Transform);

            Elem->EndPos = LoadedGame->RoomAchieverStruct.EndPos;

            for (TActorIterator<ADoor> ActorItr(GetWorld()); ActorItr; ++ActorItr){
                        
                if((*ActorItr)->ID == LoadedGame->RoomAchieverStruct.DoorID){
                    Elem->Door = (*ActorItr);
                    break;
                }

            }

            for(int i = 0; i < LoadedGame->RoomAchieverStruct.EnemiesID.Num(); i++){
                for (TActorIterator<AAIShooterPawn> ActorItr(GetWorld()); ActorItr; ++ActorItr){
                            
                    if((*ActorItr)->IDEnemy == LoadedGame->RoomAchieverStruct.EnemiesID[i]){
                        (*ActorItr)->Destroy();
                        break;
                    }

                }
            }

            Elem->FinishSpawning(LoadedGame->RoomAchieverStruct.Transform);

        }

        //Player
        APawn* Player = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
        Player->SetActorLocation(LoadedGame->PlayerPos);
        Player->SetActorRotation(LoadedGame->PlayerRot);
        
        //Load hats manually.
        if(LoadedGame->PlayerHat){
        
            ACharacterPawnQuad* MyPawn = Cast<ACharacterPawnQuad>(Player);
            MyPawn->EquipmentMesh->SetStaticMesh(HatsMesh);
            MyPawn->HatsOwned = LoadedGame->HatsID;
            MyPawn->CurrentHatMaterial = LoadedGame->CurrentHatMaterial;

            //Copy the materials that I hade before in the player.
            for(int i = 0; i < LoadedGame->HatsID.Num(); i++){
                
                TArray<UMaterialInterface *> Material;

                //Switch case to combine the hat's colors
                switch(LoadedGame->HatsID[i]){

                    case 0:
                        Material.Add(Hats[0]);
                        Material.Add(Hats[1]);
                        break;

                    case 1:
                        Material.Add(Hats[2]);
                        Material.Add(Hats[6]);
                        break;

                    case 2:
                        Material.Add(Hats[3]);
                        Material.Add(Hats[4]);
                        break;

                    case 3:
                        Material.Add(Hats[1]);
                        Material.Add(Hats[6]);
                        break;

                    case 4:
                        Material.Add(Hats[4]);
                        Material.Add(Hats[5]);
                        break;

                    case 5:
                        Material.Add(Hats[5]);
                        Material.Add(Hats[6]);
                        break;

                }
 
                MyPawn->HatMaterials.Add(Material);

            }
            
		    MyPawn->EquipmentMesh->SetMaterial(0,MyPawn->HatMaterials[MyPawn->CurrentHatMaterial][0]);
		    MyPawn->EquipmentMesh->SetMaterial(1,MyPawn->HatMaterials[MyPawn->CurrentHatMaterial][1]);
        
        }

        //GameMode
        GameMode->SetCoins(LoadedGame->Coins);
        GameMode->SetEnemies(LoadedGame->EnemiesDefeated);
        GameMode->SetAllies(LoadedGame->SpokenAllies);
        GameMode->SetStatues(LoadedGame->Statues);
        GameMode->TotalCoins = LoadedGame->TotalCoins;
        GameMode->TotalEnemies = LoadedGame->TotalEnemiesDefeated;
        GameMode->TotalAllies = LoadedGame->TotalSpokenAllies;
        GameMode->TotalStatues = LoadedGame->TotalStatues;

        //Load Speech (Done again to reset the changes)
        Speech = ConvertSpeechBack(LoadedGame->Speech);
        OldSpeech = ConvertSpeechBack(LoadedGame->OldSpeech);

        //Load ID Counters
        AGenericDestructibleElements::IDCounter = LoadedGame->DestrID;
        AEnemyAIAbstract::IDCounter = LoadedGame->EnemyID;
        APawnInteractiveClass::IDCount = LoadedGame->AllyID;

    }else{

        ArenaSpawnLocation.Add(FVector(100000.f,100000.f,0.f));
        ArenaSpawnLocation.Add(FVector(-100000.f,100000.f,0.f));
        ArenaSpawnLocation.Add(FVector(100000.f,-100000.f,0.f));
        ArenaSpawnLocation.Add(FVector(-100000.f,-100000.f,0.f));  

        LoadFromFile(Speech, "QuestionsSpeech");
        LoadFromFile(Questions, "Questions");
        LoadFromFile(BlockedSpeech, "BlockedSpeech");

        //Initialize all the components for the maze creation.
        MazeGraph = new Graph<AMazeCell2>();
        MazeActor = GetWorld()->SpawnActor<AMaze>(MazeActorClass,FVector(0,0,Depth),FRotator::ZeroRotator);
        MazeActorFloor = GetWorld()->SpawnActor<AMaze>(MazeActorClass,FVector(30,0,Depth),FRotator::ZeroRotator);

        UGameplayStatics::GetPlayerPawn(GetWorld(),0)->MoveIgnoreActorAdd(MazeActorFloor);
        
        StandardMazeCreation();

        DepthVisit(MazeGraph->GetCurrentNode());


        if(PopulateMaze){

            FVector Pos;
            TArray<AMazeCell2*> Nodes = MazeGraph->GetNodes();
            bool Dir = true;
            for(int i = 0; i < Nodes.Num(); i += 2){

                if(i % Length == 0)
                    Dir = !Dir;
                
                if(!Dir)
                    Pos = Nodes[i]->GetActorLocation();
                else
                    Pos = Nodes[i + 1]->GetActorLocation();
                
                Pos.Z = 400.f;

            }
            
            GenerateElements(MaxPath);

            //GenerateDoors();

            Populate(MaxPath);

            UE_LOG(LogTemp,Warning,TEXT("Main %i"), CellsToPopulate.MainPath.Num());
            UE_LOG(LogTemp,Warning,TEXT("Other %i"), CellsToPopulate.OtherPaths.Num());
            UE_LOG(LogTemp,Warning,TEXT("OneCell %i"), CellsToPopulate.OneCellElem.Num());
            UE_LOG(LogTemp,Warning,TEXT("Extra %i"), CellsToPopulate.ExtrElem.Num());
            UE_LOG(LogTemp,Warning,TEXT("Door %i"), CellsToPopulate.Door.Num());

            PopulateBartle();

            FTransform Transform;
            Transform.SetLocation((MaxPath[0]->GetActorLocation() + MaxPath[1]->GetActorLocation())/2);
            Transform.SetRotation(GetDoorRotation(MaxPath[1], MaxPath[0]).Quaternion());
            //Add an extra checkpoint at the beginning
            ACheckPointLevel1* Checkpoint = GetWorld()->SpawnActorDeferred<ACheckPointLevel1>(CheckPointClass,Transform);
            Checkpoint->MazeManager = this;
            Checkpoint->FinishSpawning(Transform);

            Pos = MaxPath[MaxPath.Num() - 1]->GetActorLocation();
            Pos.Z = -54.f;

            GetWorld()->SpawnActor<AFinalLevelActor>(FinalLevelActorClass, Pos, GetDoorRotation(MaxPath[MaxPath.Num() - 1],MaxPath[MaxPath.Num() - 2]));

        }

    }

    if(GetWorld() != nullptr){
    
        GetWorld()->GetTimerManager().SetTimer(StartTimer, this, &AMazeManager::StopGame, 0.2, false);
    
    }
}

void AMazeManager::StopGame(){

	ACharacterPawnQuad* Player = Cast<ACharacterPawnQuad>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
    Player->bStopMovement = false;

}

// Called every frame
void AMazeManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

#pragma endregion

#pragma region MazeCreation

void AMazeManager::StandardMazeCreation() {
    InitializeMaze();
    CreateMaze(MazeGraph->GetCurrentNode(),nullptr);
}


//Used to draw the line for the visual graph
void AMazeManager::PrintMaze(TArray<AMazeCell2*> Nodes, FColor Color) {

    for(int i = 0 ; i < Nodes.Num(); i++){
        
        if(i != Nodes.Num() - 1)

            DrawDebugLine(GetWorld(),
			FVector(Nodes[i]->GetActorLocation().X, Nodes[i]->GetActorLocation().Y, Nodes[i]->GetActorLocation().Z + 1100), //1100
			FVector(Nodes[i + 1]->GetActorLocation().X,Nodes[i + 1]->GetActorLocation().Y,Nodes[i + 1]->GetActorLocation().Z + 1100),
			Color,
			true,
			50.f,
			0,
			50.f);

    }

}

//Create the different maze cells.
void AMazeManager::InitializeMaze() {
    
    FTransform Transform;
    
    //Create the instanced mesh and creat the graph node.
    for (int i = 0; i < Height; i++) {
        TArray<AMazeCell*> Row;
        for (int j = 0; j < Length; j++) {
            
            FVector Origin(i * (-Distance) + MazeActor->GetActorLocation().X, j * Distance +MazeActor->GetActorLocation().Y, 0.f); //1100 --- 1.5

            FVector MazeActorScale = MazeActor->GetActorScale3D();
            AMazeCell2* CellActor = GetWorld()->SpawnActor<AMazeCell2>(CellClass,FVector(MazeActorScale.X * i * (-Distance),MazeActorScale.Y * j * Distance, Depth),FRotator::ZeroRotator);
            //CellActor->SetFolderPath(TEXT("MazePieces"));
            
            FAttachmentTransformRules TransformRules(EAttachmentRule::KeepWorld,true);
            CellActor->AttachToActor(MazeActor,TransformRules);

            Transform.SetLocation(Origin);
            //MazeActor->CreateFloor(Transform);
            MazeActorFloor->CreateFloor(Transform);
            MazeActor->CreateWalls(Transform);

            MazeGraph->AddNode(CellActor);

            if(i == 0 && j == 0)
                MazeGraph->SetCurrentNode(CellActor);

            TArray<AMazeCell2*> Cells = MazeGraph->GetNodes();

            //Add sides to the maze

            if(j != 0 && j % Length != 0)
                MazeGraph->AddSide(CellActor,Cells[i*Height + j-1],0);

            if(i != 0 && i % Height != 0)
                MazeGraph->AddSide(CellActor,Cells[i*Height + j - Height],0);

        }
    }

    //This second loop is used just to geenerate the first vertical wall and the last horizontal one.
    for (int i = 0; i < Height; i++) {
            
            FVector Origin(+Distance, i * Distance, 0);
            Transform.SetLocation(Origin);
            MazeActor->CreateVerticalWall(Transform);

            Origin = FVector(-Distance * i, +Distance * Length, 0);
            Transform.SetLocation(Origin);
            MazeActor->CreateHorizontalWall(Transform);

    }

}

void AMazeManager::CreateMaze(AMazeCell2* Current,AMazeCell2* Previous) {

       if(!Current->bIsVisited){
        
        Current->bIsVisited = true;
        TArray<Side<AMazeCell2>*> Neighbors = MazeGraph->GetSides(Current);

        //NumberOfTimes the for loop will be execute
        int Cycles = Neighbors.Num();
        int Contator = 0;

        while(Contator < Cycles){
            
            int NumExtr = FMath::RandRange(0, Neighbors.Num() - 1);

            Side<AMazeCell2>* MazeCell = Neighbors[NumExtr];
            
            if((MazeCell->To->bIsVisited && MazeCell->To != Previous) || MazeCell->To->bIsRoom){
            
                //if used to insert just one door.
                if(MazeCell->To->bIsRoom && !RoomWithDoor.Contains(MazeCell->To->RoomNumber)){

                    Current->DestroyWall(MazeCell->To);
                    RoomWithDoor.Add(MazeCell->To->RoomNumber);

                }else
                    MazeGraph->DeleteSide(Current,MazeCell->To);

            }else{
                Current->DestroyWall(MazeCell->To);
                CreateMaze(MazeCell->To,Current);
            }

            Neighbors.Remove(MazeCell);
            
            Contator++;

        }
    }


}

#pragma endregion

#pragma region Populate

void AMazeManager::Populate(TArray<AMazeCell2*> Path) {
    
    for(int i = 0; i < Path.Num(); i++){

        //for each sides in in the MaxPath
        for(Side<AMazeCell2>* S: MazeGraph->GetSides(Path[i])){

            //if I am not in the last cell and the next cell is not part of the MaxPath
            if(i != Path.Num() - 1 && S->To != Path[i + 1]){

                bool bCanIContinue = true;

                //if the previous cell is not part of the MaxPath
                if(i != 0 && S->To == Path[i - 1])
                    bCanIContinue = false;

                //Further check when i is equal to 0
                if(i == 0){
                    
                    if(MaxPath.Contains(S->To)){
                        
                        bCanIContinue = false;
                        break;

                    }else{

                        for(TArray<AMazeCell2*> Path : MaxPaths){
                            
                            if(Path.Contains(S->To)){
                        
                                bCanIContinue = false;
                                break;

                            }

                        }

                    }

                }

                if(bCanIContinue){
                    Graph<AMazeCell2>* NewGraph = new Graph<AMazeCell2>();
                    CreateOtherPaths(NewGraph,S->To, Path[i]);

                    NewGraph->SetVisitedToZero();
                    TArray<AMazeCell2*> MazeCellMax;
                    
                    DepthVisitWrapper(S->To,0, TArray<AMazeCell2*>(),MazeCellMax, NewGraph);

                    MaxPaths.Add(MazeCellMax);

                    FString s = "";
                    TArray<AMazeCell2*> T = NewGraph->GetNodes();

                    NewGraph->SetVisitedToZero();

                    for(int j = 0; j < MazeCellMax.Num(); j++)
                        MazeCellMax[j]->bIsVisited = true;

                    delete NewGraph;

                    //Based on the number of cells I decide how to poplate them.
                    if(MazeCellMax.Num() > 5){
                        
                        GenerateElements(MazeCellMax);

                        CellsToPopulate.ExtrElem.Add(MazeCellMax[MazeCellMax.Num() - 1], FPath(Path));
                        CellsToPopulate.Couple.Add(MazeCellMax[MazeCellMax.Num() - 1],MazeCellMax[MazeCellMax.Num() - 2]);
                        //SpawnExtraElem(FMath::RandRange(0,3),MazeCellMax[MazeCellMax.Num() - 1],MazeCellMax[MazeCellMax.Num() - 2]);
                        
                    }else{

                        //if cells are greater than 1 insert one last element
                        if(MazeCellMax.Num() > 1){

                           
                            //if its value is 3 it added one cell element
                            if(MazeCellMax.Num() > 2){

                                CellsToPopulate.OneCellElem.Add(MazeCellMax[MazeCellMax.Num() - 2], FPath(Path));       
                                //SpawnSigleCellElem(FMath::RandRange(0,3),MazeCellMax[MazeCellMax.Num() - 2]);
        
                            }
                            //if its value is 4 it added one cell element
                            if(MazeCellMax.Num() > 3){
                                //SpawnSigleCellElem(FMath::RandRange(0,3),MazeCellMax[MazeCellMax.Num() - 3]);
                                CellsToPopulate.OneCellElem.Add(MazeCellMax[MazeCellMax.Num() - 3], FPath(Path));

                            //SpawnExtraElem(FMath::RandRange(0,3),MazeCellMax[MazeCellMax.Num() - 1],MazeCellMax[MazeCellMax.Num() - 2]);

                            }
                            
                            if(MazeCellMax.Num() > 4){
                                //SpawnSigleCellElem(FMath::RandRange(0,3),MazeCellMax[MazeCellMax.Num() - 3]); 
                                CellsToPopulate.OneCellElem.Add(MazeCellMax[MazeCellMax.Num() - 4], FPath(Path));

                            //SpawnExtraElem(FMath::RandRange(0,3),MazeCellMax[MazeCellMax.Num() - 1],MazeCellMax[MazeCellMax.Num() - 2]);

                            }

                            CellsToPopulate.ExtrElem.Add(MazeCellMax[MazeCellMax.Num() - 1], FPath(Path));                        
                            CellsToPopulate.Couple.Add(MazeCellMax[MazeCellMax.Num() - 1],MazeCellMax[MazeCellMax.Num() - 2]);

                        }else{

                            //SpawnExtraElem(FMath::RandRange(0,3),MazeCellMax[MazeCellMax.Num() - 1],Path[i]);
                            CellsToPopulate.ExtrElem.Add(MazeCellMax[MazeCellMax.Num() - 1], FPath(Path));
                            CellsToPopulate.Couple.Add(MazeCellMax[MazeCellMax.Num() - 1],Path[i]);

                        }
                    }

                    Populate(MazeCellMax);

                }

            }


        }

    }

}

TArray<TArray<FString>> AMazeManager::ConvertSpeechBack(TArray<FSpeech> List){

    TArray<TArray<FString>> StringArray;
    for(int i = 0; i < List.Num(); i++){

        StringArray.Add(List[i].String);

    }

    return StringArray;

}

void AMazeManager::LoadFromFile(TArray<TArray<FString>>& List, FString FileName) {
    
    TArray<FString> StringArray;
    FString CompleteFilePath = FPaths::ProjectContentDir() + "TextFiles/" + FileName +".txt";
    UE_LOG(LogTemp, Warning, TEXT("%s"), *CompleteFilePath);
    FFileHelper::LoadFileToStringArray(StringArray,*CompleteFilePath);

    if(StringArray.Num() == 0)
        UE_LOG(LogTemp, Warning, TEXT("0 Strings"));

    for(FString String : StringArray){
        
        TArray<FString> Result;
        String.ParseIntoArray(Result, _T(","),true);
        List.Add(Result);

    }

}


void AMazeManager::DepthVisit(AMazeCell2* Start) {
    
    MazeGraph->SetVisitedToZero();
    TArray<AMazeCell2*> MazeCellMax;
    DepthVisitWrapper(Start,0, TArray<AMazeCell2*>(),MazeCellMax, MazeGraph);
    MaxPath = MazeCellMax;
    TArray<AMazeCell2*> NewPath;
    Graph<TArray<AMazeCell2*>> OtherGraph;

}

void AMazeManager::DepthVisitWrapper(AMazeCell2* Current, float Cost, TArray<AMazeCell2*> CurrentVisitedCell,
        TArray<AMazeCell2*> & MazeCellMax, Graph<AMazeCell2>* CurrentGraph) {
    
    TArray<Side<AMazeCell2>*> Sides = CurrentGraph->GetSides(Current); 
    Current->bIsVisited = true;
    CurrentVisitedCell.Add(Current);

    for(Side<AMazeCell2>* S: CurrentGraph->GetSides(Current)){
        if(S->To->bIsVisited != true)
            DepthVisitWrapper(S->To, Cost + 1, CurrentVisitedCell, MazeCellMax,CurrentGraph);
    }

    //Search for the maximum path (uncomment below to put the exit in one of the sides)
    if(CurrentVisitedCell.Num() > MazeCellMax.Num()) //&& (LastCell->I == 0 || LastCell->I == 12 ||
                                                    //    LastCell->J == 0 || LastCell->J == 12))
        MazeCellMax = CurrentVisitedCell;

}

//Creates a graph for each path which is not part of the max path.
void AMazeManager::CreateOtherPaths(Graph<AMazeCell2>* OtherGraph, AMazeCell2* Current, AMazeCell2* Previous){
    
    TArray<Side<AMazeCell2>*> Sides = MazeGraph->GetSides(Current);
    
    OtherGraph->AddNode(Current);

    for(Side<AMazeCell2>* S: Sides){

        if(Previous != nullptr && OtherGraph->Contains(Previous)) //I don't wanna insert in the graph the cell that is part of one other Max path.
            OtherGraph->AddSide(Current, Previous, 0);

        if(S->To != Previous){

            CreateOtherPaths(OtherGraph, S->To, Current);
        
        }

    }
    
}

void AMazeManager::GenerateElements(TArray<AMazeCell2*> Path) {
    
    //Used to check what is the last index for path different from Maxpath.
    int LastIndex = 0;

    //When is 3, I insert a Door.
    int DoorFrequency = 0;
    int InitialIndex = 1;
    if(Path == MaxPath)
        InitialIndex = 3;
    for(int i = InitialIndex; i < Path.Num() - 4; i += 4){ //MaxPath.Num() - 2

        LastIndex = i;

        if(DoorFrequency < 3){

            if(Path == MaxPath)

                CellsToPopulate.MainPath.Add(Path[i], FPath(Path));

            else

                CellsToPopulate.OtherPaths.Add(Path[i], FPath(Path));

            /*if(FMath::RandRange(0,2) < 2)
                AddEnemy(FMath::RandRange(0,3), Path[i], Path);
            else
                AddFallenPlatforms(FMath::RandRange(0,3), Path[i], Path);*/

            DoorFrequency += 1;
        
        }else{

            CellsToPopulate.Door.Add(Path[i], FPath(Path));
            CellsToPopulate.Couple.Add(Path[i], Path[i + 1]);
            
            /*AddDoor(FMath::RandRange(0,3),MaxPath[i]);  
            FVector Offset;
            ACheckPointLevel1* CheckPoint;

            //create the exact position for the checkpoint.
            if(SetOffsetVector(MaxPath[i + 1], MaxPath[i], Offset, 0)){
                
                FRotator Rotator = GetDoorRotation(MaxPath[i + 1], MaxPath[i]);
                if(Rotator == FRotator(0.f,180.f,0.f))
                    Offset = FVector(0.f,100.f,0.f);
                else
                    Offset = FVector(0.f,-100.f,0.f);

                CheckPoint = GetWorld()->SpawnActor<ACheckPointLevel1>(CheckPointClass,(MaxPath[i + 1]->GetActorLocation() + MaxPath[i]->GetActorLocation()) / 2 + Offset,
                    GetDoorRotation(MaxPath[i + 1], MaxPath[i]));

            }else{

                FRotator Rotator = GetDoorRotation(MaxPath[i + 1], MaxPath[i]);
                if(Rotator == FRotator(0.f,-90.f,0.f))
                    Offset = FVector(-100.f,0.f,0.f);
                else
                    Offset = FVector(100.f,0.f,0.f);

                CheckPoint = GetWorld()->SpawnActor<ACheckPointLevel1>(CheckPointClass,(MaxPath[i + 1]->GetActorLocation() + MaxPath[i]->GetActorLocation()) / 2 + Offset,
                    GetDoorRotation(MaxPath[i + 1], MaxPath[i]));
            }

            CheckPoint->MazeManager = this;*/

            i -= 2; 
            DoorFrequency = 0;

        }

        //Just for others Path to fill some cells that are still empty.
        if(Path != MaxPath){
            int Difference = Path.Num() - 4 - LastIndex;

            //Case
            if(LastIndex == 0){
                
            }

            //Possible Value: 1,2,3, 4
            switch(Difference){

                case 1:

                    // this perfect case

                    break;

                case 2:

                    // Useless

                    break;

                case 3:

                    //SpawnSigleCellElem(FMath::RandRange(0,3),Path[Path.Num() - 2]);
                    CellsToPopulate.OneCellElem.Add(Path[Path.Num() - 2], FPath(Path));

                    break;

                case 4:
                                        
                    CellsToPopulate.OneCellElem.Add(Path[Path.Num() - 2], FPath(Path));
                    CellsToPopulate.OneCellElem.Add(Path[Path.Num() - 3], FPath(Path)); 
                    //SpawnSigleCellElem(FMath::RandRange(0,3),Path[Path.Num() - 2]);
                    //SpawnSigleCellElem(FMath::RandRange(0,3),Path[Path.Num() - 3]);

                    break;

            }
        }
    
    } 

}

void AMazeManager::AddEnemy(int Index, AMazeCell2* Cell, TArray<AMazeCell2*> Path) {

    FTransform Transform;
    int CellIndex = Path.IndexOfByKey(Cell);

    switch (Index){

    case 0:

        TypeOfCoinEnemies(FMath::RandRange(0,2),CellIndex, Path);
        
        break;
    
    case 1:

        TypeOfEnemies(FMath::RandRange(0,2),CellIndex, Path);

        break;
    
    case 2:
        
        TypeOfPatrols(FMath::RandRange(0,2),CellIndex, Path);

        break;

    case 3:

        TypeOfMoveAlly(FMath::RandRange(0,2),CellIndex, Path);

        break;
    
    default:
        UE_LOG(LogTemp,Warning,TEXT("AddEnemy"));
        break;

    }

}



//Calculate the offset based on the position of the Cell (index) and return a direction of the 2 adjacent cells.
bool AMazeManager::SetOffsetVector(AMazeCell2* AheadCell, AMazeCell2* BehindCell, FVector& Offset, float Value) {
        
        if(FMath::Abs((BehindCell->GetActorLocation().X - AheadCell->GetActorLocation().X)) < 0.1f){
            Offset = FVector(Value,0.f,0.f);
            return true;
        }else{
            Offset = FVector(0.f,Value,0.f);
            return false;
        }
}

//Normal ray tracing.
void AMazeManager::LineTracing(FHitResult& Hit,FVector StartPosition, FVector EndPosition) {

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	GetWorld()->LineTraceSingleByChannel(Hit,StartPosition,EndPosition,ECollisionChannel::ECC_GameTraceChannel10,CollisionParams);

}

//It performs a ray tracing, If it doesn't find a wall, it doesn't create the obstacle.
void AMazeManager::GenerateDecorations(FVector StartPos, FVector EndPos, FVector EndLineTracingPos, bool Spawn,TSubclassOf<AGenericDestructibleElements> SpawnActor) {
    
    FTransform Transform;
    Transform.SetRotation(FRotator::ZeroRotator.Quaternion());
    
    FHitResult Hit;

    LineTracing(Hit,StartPos,EndLineTracingPos);
    if(Hit.GetActor() != nullptr){
        Transform.SetLocation(EndPos);
        if(!Spawn)
            MazeActor->CreateObstacle(Transform);
        else
            GetWorld()->SpawnActor<AGenericDestructibleElements>(SpawnActor,Transform);      
        
    }

}

void AMazeManager::TypeOfPatrols(int Index, int CellIndex, TArray<AMazeCell2*> Path) {
    
    IInterfaceMovableAI* Enemy;
    FVector Offset;
    FVector LastOffset;
    FTransform Transform;
    
    switch (Index){

    case 0:
        
        Transform.SetLocation(Path[CellIndex]->GetActorLocation());
        Transform.SetRotation(FRotator::ZeroRotator.Quaternion());
        //Here I create the enemy
        Enemy = GetWorld()->SpawnActorDeferred<IInterfaceMovableAI>(PatrolEnemyClass,Transform);

        /*for the number of cells I consider (This case 3), I check the position beetween the current Cell and the next one,
        and generate one obstacle in near the center of the cell and in the middle between two cells. (If I create an obstacle
        where there is not a wall, I delete it.)*/
        for(int i = 0; i< 3; i++){

            Enemy->Positions.Add(Path[CellIndex + i]->GetActorLocation());

            GenerateSideElements(CellIndex,i, 0.f, -25.f, 320.f, false, nullptr, Path);

        }
        
        Cast<APawn>(Enemy)->FinishSpawning(Transform);

        break;

    case 1:

        GenerateSideActor(PatrolEnemyClass,PatrolEnemyClass,CellIndex,Path, true, 220.f);
        break;

    case 2:

        //Create the patrols for the first and the third cell.
        for(int i = 0; i< 3; i += 2){

            //Here I create the enemy
            Transform.SetLocation(Path[CellIndex + i]->GetActorLocation());
            Transform.SetRotation(FRotator::ZeroRotator.Quaternion());
            Enemy = GetWorld()->SpawnActorDeferred<IInterfaceMovableAI>(PatrolEnemyClass,Transform);

            SetOffsetVector(Path[CellIndex + 1 + i],Path[CellIndex + i],Offset,350);

            Enemy->Positions.Add(Path[CellIndex + i]->GetActorLocation() + Offset);
            Enemy->Positions.Add(Path[CellIndex + i]->GetActorLocation() - Offset);
            
            Cast<APawn>(Enemy)->FinishSpawning(Transform);
        
        }

        Transform.SetRotation(FRotator::ZeroRotator.Quaternion());
        Transform.SetLocation(Path[CellIndex + 1]->GetActorLocation());
        MazeActor->CreateObstacle(Transform);

        AddDoubleCircularPatrol(Path[CellIndex + 1]);
        
        break;

    default:
        UE_LOG(LogTemp,Warning,TEXT("TypeOfPatrols"));
        break;

    }

}

void AMazeManager::AddDoubleCircularPatrol(AMazeCell2* Cell) {

    IInterfaceMovableAI* Enemy;
    FTransform Transform;

    //Create 2 patrols for the second cell (Circular movement) in the opposite way.
    for(int i = 0; i < 2; i ++){

        //Here I create the enemy
        if(i == 0)
            Transform.SetLocation(Cell->GetActorLocation() + FVector(300.f,300.f,0.f));
        else
            Transform.SetLocation(Cell->GetActorLocation() + FVector(-300.f,-300.f,0.f));

        Enemy = GetWorld()->SpawnActorDeferred<IInterfaceMovableAI>(PatrolEnemyCircularClass, Transform);

        //Enemy = GetWorld()->SpawnActorDeferred<IInterfaceMovableAI>(PatrolEnemyCircularClass,Transform);
        Enemy->Positions.Add(Cell->GetActorLocation() + FVector(300.f,300.f,0.f));
        Enemy->Positions.Add(Cell->GetActorLocation() + FVector(-300.f,300.f,0.f));
        Enemy->Positions.Add(Cell->GetActorLocation() + FVector(-300.f,-300.f,0.f));
        Enemy->Positions.Add(Cell->GetActorLocation() + FVector(300.f,-300.f,0.f));

        if(i != 0)
            Cast<APatrolAI2>(Enemy)->StartIndex = 2;

        //I wanna a circular movement.
        Cast<APatrolAI2>(Enemy)->StartDirection = false;
        Cast<APawn>(Enemy)->FinishSpawning(Transform);

    }

}

void AMazeManager::TypeOfMoveAlly(int Index, int CellIndex, TArray<AMazeCell2*> Path) {
    
    IInterfaceMovableAI* Enemy;
    FTransform Transform;

    switch (Index){

    case 0:
        
        for(int i = 0; i < 3; i++){
            Transform.SetLocation(Path[CellIndex + i]->GetActorLocation());
            Enemy = GetWorld()->SpawnActorDeferred<IInterfaceMovableAI>(MoveAIClass2,Transform);
            Enemy->Positions.Add(Path[CellIndex + i]->GetActorLocation());
            Cast<APawn>(Enemy)->FinishSpawning(Transform);
            AddSpeech(Cast<APawnInteractiveClass>(Enemy));
        }

        break;

    case 1:

        GenerateSideActor(MoveAIClass,MoveAIClass,CellIndex, Path, true, 220.f);
        
        break;

    case 2:

        Transform.SetLocation((Path[CellIndex + 1]->GetActorLocation() + Path[CellIndex + 2]->GetActorLocation())/2);
        Enemy = GetWorld()->SpawnActorDeferred<IInterfaceMovableAI>(MoveAIClass2,Transform);
        Enemy->Positions.Add((Path[CellIndex + 1]->GetActorLocation() + Path[CellIndex + 2]->GetActorLocation())/2);
        Cast<APawn>(Enemy)->FinishSpawning(Transform);
        AddSpeech(Cast<APawnInteractiveClass>(Enemy));
    
        for(int i = 0; i < 3; i = i + 2){
    
            Transform.SetLocation((Path[CellIndex + i]->GetActorLocation() + Path[CellIndex + i + 1]->GetActorLocation()) / 2);
            Transform.SetRotation(GetDoorRotation(Path[CellIndex + i + 1],Path[CellIndex + i]).Quaternion());
            ADoorRiddle* Door = GetWorld()->SpawnActorDeferred<ADoorRiddle>(DoorRiddleClass,Transform);
            Cast<ADoorRiddle>(Door)->Speech = &Speech;
            Cast<ADoorRiddle>(Door)->OldSpeech = &OldSpeech;
            Cast<ADoorRiddle>(Door)->Questions = &Questions;
            Cast<ADoorRiddle>(Door)->OldQuestions = &OldQuestions;
            Door->FinishSpawning(Transform);
    
        }

        break;

    default:
        UE_LOG(LogTemp,Warning,TEXT("TypeOfMoveAlly"));
        break;

    }

}

//generate two actor in the sides of a cell and adds obstacles in the middle. (for 3 cells)
void AMazeManager::GenerateSideActor(TSubclassOf<APawn> AIClass1, TSubclassOf<APawn> AIClass2, int CellIndex, TArray<AMazeCell2*> Path, bool bObstacle, float OffsetValue) {
        
        IInterfaceMovableAI* Enemy;
        IInterfaceMovableAI* SecondEnemy;
        FVector Offset;
        FVector LastOffset;
        FTransform Transform;
        FTransform Transform1;
        FTransform Transform2;

        //Generate an Offset based on the position of two cells.
        SetOffsetVector(MaxPath[CellIndex + 1],Path[CellIndex],Offset,OffsetValue);

        //Generate two enemies.
        Transform1.SetLocation(Path[CellIndex]->GetActorLocation() + Offset);
        Transform1.SetRotation(FRotator::ZeroRotator.Quaternion());
        Enemy = GetWorld()->SpawnActorDeferred<IInterfaceMovableAI>(AIClass1,Transform1);

        Transform2.SetLocation(Path[CellIndex]->GetActorLocation() - Offset);
        Transform2.SetRotation(FRotator::ZeroRotator.Quaternion());
        SecondEnemy = GetWorld()->SpawnActorDeferred<IInterfaceMovableAI>(AIClass2,Transform2);

        /*for the number of cells I consider (This case 3), I assign the new position to the patrol's array. The offset is used
        to arrange the position.*/
        for(int i = 0; i < 3; i++){
            LastOffset = Offset;

            SetOffsetVector(Path[CellIndex + 1 + i],Path[CellIndex + i],Offset,OffsetValue);
            if(LastOffset != Offset){

                Enemy->Positions.Add(Path[CellIndex + i]->GetActorLocation() + Offset + LastOffset);
                SecondEnemy->Positions.Add(Path[CellIndex + i]->GetActorLocation() - Offset - LastOffset);

            }else{

                Enemy->Positions.Add(Path[CellIndex + i]->GetActorLocation() + Offset);
                SecondEnemy->Positions.Add(Path[CellIndex + i]->GetActorLocation() - Offset);

            }

            if(bObstacle){
                //Every cycle I insert an obstacle.
                Transform.SetLocation(Path[CellIndex + i]->GetActorLocation() + FVector(0.f,0.f,0.f));
                MazeActor->CreateObstacle(Transform);
            }
        }

        Cast<APawn>(Enemy)->FinishSpawning(Transform1);
        Cast<APawn>(SecondEnemy)->FinishSpawning(Transform2);

        //AddSpeech if actors are APawnInteractiveClass
        if(Cast<APawn>(Enemy)->IsA(APawnInteractiveClass::StaticClass())){

            AddSpeech(Cast<APawnInteractiveClass>(Enemy));

        }

        if(Cast<APawn>(SecondEnemy)->IsA(APawnInteractiveClass::StaticClass())){

            AddSpeech(Cast<APawnInteractiveClass>(SecondEnemy));

        }

}

//Generate walls one beside the middle ad one in the angle.
void AMazeManager::GenerateSideElements(int CellIndex, int i, float HeightOffset, float SideOffset, float OffsetValue, bool Spawn,TSubclassOf<AGenericDestructibleElements> SpawnActor, TArray<AMazeCell2*> Path) {
    
    FVector Offset;
    SetOffsetVector(Path[CellIndex + 1 + i],Path[CellIndex + i],Offset,OffsetValue);

    GenerateDecorations(Path[CellIndex + i]->GetActorLocation(),
        Path[CellIndex + i]->GetActorLocation() + Offset + FVector(0.f,0.f,0),
        Path[CellIndex + i]->GetActorLocation() + 2 * Offset ,
        Spawn,SpawnActor);
    
    bool Value = SetOffsetVector(Path[CellIndex + 1 + i],Path[CellIndex + i],Offset,OffsetValue);

    if(Value)

        GenerateDecorations(Path[CellIndex + i]->GetActorLocation(),
            (Path[CellIndex + i]->GetActorLocation() + Path[CellIndex + i + 1]->GetActorLocation())/2 - Offset + FVector(0.f,SideOffset,0),
            (Path[CellIndex + i]->GetActorLocation() + Path[CellIndex + i + 1]->GetActorLocation())/2 - 2 * Offset + FVector(0.f,SideOffset,0),
            Spawn,SpawnActor);

    else
        
        GenerateDecorations(Path[CellIndex + i]->GetActorLocation(),
            (Path[CellIndex + i]->GetActorLocation() + Path[CellIndex + i + 1]->GetActorLocation())/2 - Offset + FVector(SideOffset,0.f,0) ,
            (Path[CellIndex + i]->GetActorLocation() + Path[CellIndex + i + 1]->GetActorLocation())/2 - 2 * Offset + FVector(SideOffset,0.f,0),
            Spawn,SpawnActor);

}

void AMazeManager::TypeOfEnemies(int Index, int CellIndex, TArray<AMazeCell2*> Path) {
    
    FVector Offset;
    FVector Pos;
    FTransform Transform;

    switch(Index){

        case 0:

            GetWorld()->SpawnActor<AAIShooterPawn>(ShooterEnemyClass,Path[CellIndex]->GetActorLocation() , FRotator::ZeroRotator);
            GetWorld()->SpawnActor<AAIShooterPawn>(ShooterEnemyClass,Path[CellIndex + 2]->GetActorLocation() , FRotator::ZeroRotator);
            GenerateSideElements(CellIndex,0, 0.f, -25.f, 320.f, false, nullptr, Path);
            GenerateSideElements(CellIndex,1, 0.f, -25.f, 320.f, false, nullptr, Path);
            GenerateSideElements(CellIndex,2, 0.f, -25.f, 320.f, false, nullptr, Path);

            break;
        
        case 1:

            SetOffsetVector(Path[CellIndex + 1],Path[CellIndex],Offset,220.f);
            Pos = (Path[CellIndex]->GetActorLocation() + Path[CellIndex + 1]->GetActorLocation()) / 2;
            GetWorld()->SpawnActor<AAIBull>(BullEnemyClass, Pos + Offset/2, FRotator::ZeroRotator);
            GetWorld()->SpawnActor<AAIBull>(BullEnemyClass,Path[CellIndex + 2]->GetActorLocation() , FRotator::ZeroRotator);
            GenerateSideElements(CellIndex,0, 0.f, -25.f, 320.f, false, nullptr, Path);
            GenerateSideElements(CellIndex,1, 0.f, -25.f, 320.f, false,  nullptr, Path);
            GenerateSideElements(CellIndex,2, 0.f, -25.f, 320.f, false, nullptr, Path);

            break;

        case 2:
            
            SetOffsetVector(Path[CellIndex + 1],Path[CellIndex],Offset,100.f);
            Pos = (Path[CellIndex]->GetActorLocation() + Path[CellIndex + 1]->GetActorLocation()) / 2;
            
            GetWorld()->SpawnActor<AAIBull>(BullEnemyClass, Path[CellIndex + 1]->GetActorLocation(), GetDoorRotation(MaxPath[CellIndex + 1], MaxPath[CellIndex]));
            GetWorld()->SpawnActor<AAIBull>(BullEnemyClass, Path[CellIndex + 1]->GetActorLocation() + Offset, GetDoorRotation(MaxPath[CellIndex + 1], MaxPath[CellIndex]));
           
            GetWorld()->SpawnActor<AAIShooterPawn>(ShooterEnemyClass,Path[CellIndex + 2]->GetActorLocation() , FRotator::ZeroRotator);
            GetWorld()->SpawnActor<AAIShooterPawn>(ShooterEnemyClass,Path[CellIndex]->GetActorLocation() , FRotator::ZeroRotator);

            Transform.SetLocation((Path[CellIndex]->GetActorLocation() + Path[CellIndex + 1]->GetActorLocation()) / 2 + FVector(0.f,0.f,-70.f));
            Transform.SetRotation(GetDoorRotation(Path[CellIndex + 1], Path[CellIndex]).Quaternion());
            MazeActorFloor->CreateMetalCrate(Transform);

            Transform.SetLocation((Path[CellIndex + 1]->GetActorLocation() + Path[CellIndex + 2]->GetActorLocation()) / 2 + FVector(0.f,0.f,-70.f));
            Transform.SetRotation(GetDoorRotation(Path[CellIndex + 2], Path[CellIndex + 1]).Quaternion());
            MazeActorFloor->CreateMetalCrate(Transform);
        
            GenerateSideElements(CellIndex,0, 0.f, -25.f, 320.f, false, nullptr, Path);
            GenerateSideElements(CellIndex,1, 0.f, -25.f, 320.f, false,  nullptr, Path);
            GenerateSideElements(CellIndex,2, 0.f, -25.f, 320.f, false, nullptr, Path);

            break;
        
        default:
            UE_LOG(LogTemp,Warning,TEXT("TypeOfEnemies"));
            break;
    }

}

void AMazeManager::TypeOfCoinEnemies(int Index, int CellIndex, TArray<AMazeCell2*> Path) {
    
    FVector Offset;
    FVector Pos;
    AEnemyAIAbstract* Enemy;

    switch(Index){

        case 0:

            Enemy = GetWorld()->SpawnActor<AAIShooterPawn>(ShooterEnemyClass,Path[CellIndex]->GetActorLocation() , FRotator::ZeroRotator);
            Enemy->bSpawnCoin = true;
            Enemy = GetWorld()->SpawnActor<AAIShooterPawn>(ShooterEnemyClass,Path[CellIndex + 2]->GetActorLocation() , FRotator::ZeroRotator);
            Enemy->bSpawnCoin = true;

            //Create Crate Actors.
            for(int i = 0; i < 3; i++)       
                GenerateSideElements(CellIndex + i,0, 5.f, 60.f, 290.f, true,DestrCrateClass, Path);

            break;
        
        case 1:
            
            SetOffsetVector(Path[CellIndex + 1],Path[CellIndex],Offset,110.f); //110
            Pos = (Path[CellIndex]->GetActorLocation() + Path[CellIndex + 1]->GetActorLocation()) / 2 + Offset;
            
            Enemy = GetWorld()->SpawnActor<AAIBull>(BullEnemyClass, Pos + Offset , FRotator::ZeroRotator);
            Enemy->bSpawnCoin = true;
            Enemy = GetWorld()->SpawnActor<AAIBull>(BullEnemyClass,Path[CellIndex + 2]->GetActorLocation(), FRotator::ZeroRotator);
            Enemy->bSpawnCoin = true;

            //Create Crate Actors.
            for(int i = 0; i < 3; i++)       
                GenerateSideElements(CellIndex + i,0, 5.f, 60.f, 290.f, true,DestrCrateClass, Path);

            break;

        case 2:

            /*for(int i = 0; i < 3; i++){

                //Create traps in 2 cells out of 3.
                if(i != 1){

                    GetWorld()->SpawnActor<ATrap>(TrapClass, Path[CellIndex + i]->GetActorLocation() + FVector(0.f,0.f,-56.f), FRotator::ZeroRotator);
                    GetWorld()->SpawnActor<ATrap>(TrapClass, Path[CellIndex + i]->GetActorLocation() + FVector(260.f,260.f,-56.f), FRotator::ZeroRotator);
                    GetWorld()->SpawnActor<ATrap>(TrapClass, Path[CellIndex + i]->GetActorLocation() + FVector(-260.f,260.f,-56.f), FRotator::ZeroRotator);
                    GetWorld()->SpawnActor<ATrap>(TrapClass, Path[CellIndex + i]->GetActorLocation() + FVector(260.f,-260.f,-56.f), FRotator::ZeroRotator);
                    GetWorld()->SpawnActor<ATrap>(TrapClass, Path[CellIndex + i]->GetActorLocation() + FVector(-260.f,-260.f,-56.f), FRotator::ZeroRotator);

                    TArray<FVector> Positions{FVector(0.f,260.f,-56.f),FVector(0.f,-260.f,-56.f),
                        FVector(260.f,0.f,-56.f),FVector(-260.f,0.f,-56.f)};

                    // Create others element in the space empty
                    for(int j = 0; j < Positions.Num(); j++){
                        
                        if(FMath::RandRange(0,9) < 7){
                            
                            if(FMath::RandRange(0,9) < 9)
                                GetWorld()->SpawnActor<ACoinController>(CoinHorizontalClass, Path[CellIndex + i]->GetActorLocation() + Positions[j], FRotator::ZeroRotator);
                            else
                                GetWorld()->SpawnActor<AHeart>(HeartClass, Path[CellIndex + i]->GetActorLocation() + Positions[j], FRotator::ZeroRotator);

                        }

                    }

                }else{
                    
                    //Create 4 barrels and a coin in the 2 cell.
                    GetWorld()->SpawnActor<ACoinController>(CoinHorizontalClass, Path[CellIndex + i]->GetActorLocation(),FRotator::ZeroRotator);
                    GetWorld()->SpawnActor<AGenericDestructibleElements>(DestrElem,Path[CellIndex + i]->GetActorLocation() + FVector(260.f,260.f,-56.f),FRotator::ZeroRotator);
                    GetWorld()->SpawnActor<AGenericDestructibleElements>(DestrElem,Path[CellIndex + i]->GetActorLocation() + FVector(-260.f,260.f,-56.f),FRotator::ZeroRotator);
                    GetWorld()->SpawnActor<AGenericDestructibleElements>(DestrElem,Path[CellIndex + i]->GetActorLocation() + FVector(260.f,-260.f,-56.f),FRotator::ZeroRotator);
                    GetWorld()->SpawnActor<AGenericDestructibleElements>(DestrElem,Path[CellIndex + i]->GetActorLocation() + FVector(-260.f,-260.f,-56.f),FRotator::ZeroRotator);

                }

            }*/

                GenerateSideActor(StormClassFire,StormClassThunder,CellIndex, Path, false, 150.f);

                for(int i = 0; i < 3; i++){

                    SetOffsetVector(Path[CellIndex + 1 + i],Path[CellIndex + i],Offset,220.f);
                    GetWorld()->SpawnActor<ACoinController>(CoinHorizontalClass, Path[CellIndex + i]->GetActorLocation(),FRotator::ZeroRotator);
                    GetWorld()->SpawnActor<ACoinController>(CoinHorizontalClass, (Path[CellIndex + i]->GetActorLocation() + Path[CellIndex + i + 1]->GetActorLocation())/2 + Offset,FRotator::ZeroRotator);
                    GetWorld()->SpawnActor<ACoinController>(CoinHorizontalClass, (Path[CellIndex + i]->GetActorLocation() + Path[CellIndex + i + 1]->GetActorLocation())/2 - Offset,FRotator::ZeroRotator);

                }

            break;
        
        default:
            UE_LOG(LogTemp,Warning,TEXT("TypeOfCoinEnemies"));
            break;

    }

}

void AMazeManager::AddDoor(int Index, AMazeCell2* Cell, TArray<AMazeCell2*> Path) {

    int CellIndex = Path.IndexOfByKey(Cell);
    ADoor* Actor;
    FTransform Transform;

    switch(Index){
        
        //Achiever
        case 0:
            
            GetWorld()->SpawnActor<ADoorAchiever>(DoorAchieverClass, (Path[CellIndex]->GetActorLocation() + Path[CellIndex + 1]->GetActorLocation())/2,
                    GetDoorRotation(Path[CellIndex + 1], Path[CellIndex]));

            break;

        //Killer
        case 1:

            GetWorld()->SpawnActor<ADoorKiller>(DoorKillerClass, (Path[CellIndex]->GetActorLocation() + Path[CellIndex + 1]->GetActorLocation())/2,
            GetDoorRotation(Path[CellIndex + 1], Path[CellIndex]));

            break;

        //Explorer
        case 2:

            GetWorld()->SpawnActor<ADoorExplorer>(DoorExplorerClass, (Path[CellIndex]->GetActorLocation() + Path[CellIndex + 1]->GetActorLocation())/2,
                GetDoorRotation(Path[CellIndex + 1], Path[CellIndex]));

            break;

        //Socializer
        case 3:
          
            Transform.SetLocation((Path[CellIndex]->GetActorLocation() + Path[CellIndex + 1]->GetActorLocation())/2);
            Transform.SetRotation(GetDoorRotation(Path[CellIndex + 1], Path[CellIndex]).Quaternion());
            Actor = GetWorld()->SpawnActorDeferred<ADoorRiddle>(DoorRiddleClass,Transform);
            Cast<ADoorRiddle>(Actor)->Speech = &Speech;
            Cast<ADoorRiddle>(Actor)->OldSpeech = &OldSpeech;
            Cast<ADoorRiddle>(Actor)->Questions = &Questions;
            Cast<ADoorRiddle>(Actor)->OldQuestions = &OldQuestions;
            Actor->FinishSpawning(Transform);

            break;

        default:
            UE_LOG(LogTemp,Warning,TEXT("AddDoor"));
            break;
    }
    
}

FRotator AMazeManager::GetDoorRotation(AMazeCell2* AheadCell, AMazeCell2* BehindCell) {
       
    FVector Offset;
    FVector ParentOffset = MazeActor->GetActorLocation();

    if(SetOffsetVector(AheadCell, BehindCell, Offset,0.f)){

       //Need to check the exact orientation of the actor by compare The Y (X) value.
        if(FMath::Abs(AheadCell->GetActorLocation().Y - ParentOffset.Y) > FMath::Abs(BehindCell->GetActorLocation().Y - ParentOffset.Y))

            return FRotator(0.f,180.f,0.f);

        else

            return FRotator::ZeroRotator;

    }else{
                
        if(FMath::Abs(AheadCell->GetActorLocation().X - ParentOffset.X) > FMath::Abs(BehindCell->GetActorLocation().X - ParentOffset.X))
                
            return FRotator(0.f,-90.f,0.f);
                
        else

            return FRotator(0.f,90.f,0.f);

    }

}

void AMazeManager::AddFallenPlatforms(int Index, AMazeCell2* Cell, TArray<AMazeCell2*> Path) {
    
    IInterfaceMovableAI* Enemy;
    int CellIndex = Path.IndexOfByKey(Cell);
    float OffsetX;
    float OffsetY;
    FTransform Transform;
    FTransform Transform2;
    
    Cell->DestroyFloor();
    CreatePlatforms(Cell,150.f);
            
    Path[CellIndex + 2]->DestroyFloor();
    CreatePlatforms(Path[CellIndex + 2],150.f);
    
    GetWorld()->SpawnActor<ACoinController>(CoinClass,Path[CellIndex]->GetActorLocation() - FVector(0.f,0.f,10.f),Path[CellIndex]->GetActorRotation());          
    GetWorld()->SpawnActor<ACoinController>(CoinClass,Path[CellIndex + 2]->GetActorLocation() - FVector(0.f,0.f,10.f),Path[CellIndex + 2]->GetActorRotation());          

    switch(Index){

        //Achiever
        case 0:

            GetWorld()->SpawnActor<AGenericDestructibleElements>(DestrCrateClass,Path[CellIndex + 1]->GetActorLocation() + FVector(0.f,0.f,5.f),Path[CellIndex + 1]->GetActorRotation());
            OffsetX = FMath::RandRange(100.f,200.f);
            OffsetY = FMath::RandRange(100.f,200.f);
            GetWorld()->SpawnActor<AAIShooterPawn>(ShooterEnemyClass,Path[CellIndex + 1]->GetActorLocation() + FVector(OffsetX,OffsetY,10.f),Path[CellIndex + 1]->GetActorRotation())->bSpawnCoin = true;

            break;
        
        //Killer
        case 1:

            OffsetX = FMath::RandRange(100.f,200.f);
            OffsetY = FMath::RandRange(100.f,200.f);
            GetWorld()->SpawnActor<AAIShooterPawn>(ShooterEnemyClass,Path[CellIndex + 1]->GetActorLocation() + FVector(-OffsetX,-OffsetY,10.f),Path[CellIndex + 1]->GetActorRotation());
            GetWorld()->SpawnActor<AAIShooterPawn>(ShooterEnemyClass,Path[CellIndex + 1]->GetActorLocation() + FVector(OffsetX,OffsetY,10.f),Path[CellIndex + 1]->GetActorRotation());

            break;
        
        //Explorer
        case 2:
            
            if(FMath::RandRange(0,1) == 0){

                Transform.SetLocation(Path[CellIndex + 1]->GetActorLocation()  + FVector(250.f,250.f,-10.f));
                Enemy = GetWorld()->SpawnActorDeferred<IInterfaceMovableAI>(PatrolEnemyClass,Transform);
                Enemy->Positions.Add(Path[CellIndex + 1]->GetActorLocation() + FVector(300.f,300.f,-10.f));
                Enemy->Positions.Add(Path[CellIndex + 1]->GetActorLocation() + FVector(-300.f,-300.f,-10.f));
                
            }else{

                Transform.SetLocation(Path[CellIndex + 1]->GetActorLocation() +  FVector(250.f,-250.f,-10.f));
                Enemy = GetWorld()->SpawnActorDeferred<IInterfaceMovableAI>(PatrolEnemyClass,Transform);
                Enemy->Positions.Add(Path[CellIndex + 1]->GetActorLocation() + FVector(300.f,-300.f,-10.f));
                Enemy->Positions.Add(Path[CellIndex + 1]->GetActorLocation() + FVector(-300.f,300.f,-10.f));
                
            }

            Cast<APawn>(Enemy)->FinishSpawning(Transform);

            break;
        
        //Socializer
        case 3:

            OffsetX = FMath::RandRange(100.f,200.f);
            OffsetY = FMath::RandRange(100.f,200.f);

            //Done in this way to set the initial position in the vector POSITIONS.
            Transform.SetLocation(Path[CellIndex + 1]->GetActorLocation() + FVector(OffsetX,OffsetY,10.f));
            Enemy = GetWorld()->SpawnActorDeferred<IInterfaceMovableAI>(MoveAIClass2,Transform);
            Enemy->Positions.Add(Path[CellIndex + 1]->GetActorLocation());
            Cast<APawn>(Enemy)->FinishSpawning(Transform);
            AddSpeech(Cast<APawnInteractiveClass>(Enemy));


            Transform2.SetLocation(Path[CellIndex + 1]->GetActorLocation() + FVector(-OffsetX,-OffsetY,10.f));
            Enemy = GetWorld()->SpawnActorDeferred<IInterfaceMovableAI>(MoveAIClass2,Transform2);
            Enemy->Positions.Add(Path[CellIndex + 1]->GetActorLocation());
            Cast<APawn>(Enemy)->FinishSpawning(Transform2);
            AddSpeech(Cast<APawnInteractiveClass>(Enemy));

            break;

    }

}

void AMazeManager::CreatePlatforms(AMazeCell2* Cell, float Value) {
    
    GetWorld()->SpawnActor<AShakingFallenPlatform>(ShakingFallenPlatform,Cell->GetActorLocation() + FVector(0.f,0.f,-60.f),Cell->GetActorRotation());

}

void AMazeManager::PortalType(int Index, AMazeCell2* Cell) {
    
    ARoomKiller* RoomKiller;
    ARoomSocializer* RoomSocializer;
    ARoomAchiever* RoomAchiever;
    ADoor* Door;
    APuzzleButtonPortal* ButtonPortal;
    FTransform SpawnLocAndRotation;
    AMazeManager* MazeManager;
    //ASocializerMaze* SocializerMaze;
    APortal* StartPortal;
    APortalNight* StartPortalNight;
    int CellIndex = MaxPath.IndexOfByKey(Cell);
    int NumExtr;

    switch(Index){

        //Achiever
        case 0 :
            
            Door = GetWorld()->SpawnActor<ADoor>(DoorClass,  (MaxPath[CellIndex]->GetActorLocation() + MaxPath[CellIndex + 1]->GetActorLocation())/2,
                GetDoorRotation(MaxPath[CellIndex + 1], MaxPath[CellIndex]));

            NumExtr = FMath::RandRange(0,ArenaSpawnLocation.Num()-1);
            SpawnLocAndRotation.SetLocation(ArenaSpawnLocation[NumExtr]);
            RoomAchiever = GetWorld()->SpawnActor<ARoomAchiever>(RoomAchieverClass, SpawnLocAndRotation);
            RoomAchiever->EndPos = MaxPath[CellIndex]->GetActorLocation();
            RoomAchiever->Door = Door;
            ArenaSpawnLocation.RemoveAt(NumExtr);

            //Create the portal
            SpawnLocAndRotation.SetLocation(MaxPath[CellIndex]->GetActorLocation() - FVector(0.f,0.f,+50.f));
            SpawnLocAndRotation.SetRotation(FRotator::ZeroRotator.Quaternion());
            StartPortal = GetWorld()->SpawnActorDeferred<APortal>(PortalClass, SpawnLocAndRotation);
            StartPortal->NewPosition = RoomAchiever->StartSpawnPosition->GetComponentLocation();
            StartPortal->FinishSpawning(SpawnLocAndRotation);
            
            break;

        //Killer
        case 1:

            //Create the door
            Door = GetWorld()->SpawnActor<ADoor>(DoorClass,  (MaxPath[CellIndex]->GetActorLocation() + MaxPath[CellIndex + 1]->GetActorLocation())/2,
                GetDoorRotation(MaxPath[CellIndex + 1], MaxPath[CellIndex]));

            //Extract a position and spawn the room
            NumExtr = FMath::RandRange(0,ArenaSpawnLocation.Num()-1);
            SpawnLocAndRotation.SetLocation(ArenaSpawnLocation[NumExtr]);
            RoomKiller = GetWorld()->SpawnActor<ARoomKiller>(KillerRoomClass, SpawnLocAndRotation);
            RoomKiller->Door = Door;
            ArenaSpawnLocation.RemoveAt(NumExtr);

            //Create the portal
            SpawnLocAndRotation.SetLocation(MaxPath[CellIndex]->GetActorLocation() - FVector(0.f,0.f,+50.f));
            SpawnLocAndRotation.SetRotation(FRotator::ZeroRotator.Quaternion());
            StartPortal = GetWorld()->SpawnActorDeferred<APortal>(PortalClass, SpawnLocAndRotation);
            StartPortal->NewPosition = RoomKiller->SpawnPositions->GetComponentLocation() + FVector(-100.f,-100.f,+50.f);
            StartPortal->FinishSpawning(SpawnLocAndRotation);

            RoomKiller->StartPortalPos = MaxPath[CellIndex]->GetActorLocation();

            break;

        //Explorer
        case 2:

            //Create the maze
            MazeManager = GetWorld()->SpawnActorDeferred<AMazeManager>(this->GetClass(), SpawnLocAndRotation);
            MazeManager->Depth = -750.f;
            MazeManager->Length = 5;
            MazeManager->Height = 5;
            MazeManager->MazeRooms = 0;
            MazeManager->PopulateMaze = false;
            MazeManager->FinishSpawning(SpawnLocAndRotation);
            
            NumExtr = FMath::RandRange(0,ArenaSpawnLocation.Num()-1);
            MazeManager->MazeActor->SetActorLocation(ArenaSpawnLocation[NumExtr]);
            MazeManager->MazeActorFloor->SetActorLocation(ArenaSpawnLocation[NumExtr]);
            ArenaSpawnLocation.RemoveAt(NumExtr);

            //Create the door
            Door = GetWorld()->SpawnActor<ADoor>(DoorClass,  (MaxPath[CellIndex]->GetActorLocation() + MaxPath[CellIndex + 1]->GetActorLocation())/2,
                GetDoorRotation(MaxPath[CellIndex + 1], MaxPath[CellIndex]));
 
            //Create the portal
            StartPortalNight = GetWorld()->SpawnActor<APortalNight>(PortalNightClass, MaxPath[CellIndex]->GetActorLocation() - FVector(0.f,0.f,+50.f), FRotator::ZeroRotator);
            StartPortalNight->NewPosition = MazeManager->MazeGraph->GetNodes()[0]->GetActorLocation();

            //Create the puzzle
            SpawnLocAndRotation.SetLocation(MazeManager->MaxPath[MazeManager->MaxPath.Num() - 1]->GetActorLocation() + FVector(0.f,0.f,-35.f));
            SpawnLocAndRotation.SetRotation(MazeManager->MaxPath[MazeManager->MaxPath.Num() - 1]->GetActorRotation().Quaternion());
            ButtonPortal = GetWorld()->SpawnActorDeferred<APuzzleButtonPortal>(PuzzleButtonPortalClass, SpawnLocAndRotation);
            ButtonPortal->Door = Door;
            ButtonPortal->StartPortal = StartPortalNight;
            ButtonPortal->EndSpawnPosition = MazeManager->MaxPath[MazeManager->MaxPath.Num() - 2]->GetActorLocation() - FVector(0.f,0.f,50.f);
            ButtonPortal->FinishSpawning(SpawnLocAndRotation);


            break;

        //Socializer
        case 3:

            //Create the door
            Door = GetWorld()->SpawnActor<ADoor>(DoorClass,  (MaxPath[CellIndex]->GetActorLocation() + MaxPath[CellIndex + 1]->GetActorLocation())/2,
                GetDoorRotation(MaxPath[CellIndex + 1], MaxPath[CellIndex]));

            //Extract a position and spawn the room
            NumExtr = FMath::RandRange(0,ArenaSpawnLocation.Num()-1);
            SpawnLocAndRotation.SetLocation(ArenaSpawnLocation[NumExtr] - FVector(0.f,0.f,100.f));
            RoomSocializer = GetWorld()->SpawnActor<ARoomSocializer>(SocializerRoomClass, SpawnLocAndRotation);
            RoomSocializer->Door = Door;
            ArenaSpawnLocation.RemoveAt(NumExtr);

            //Create the portal
            SpawnLocAndRotation.SetLocation(MaxPath[CellIndex]->GetActorLocation() - FVector(0.f,0.f,+50.f));
            SpawnLocAndRotation.SetRotation(FRotator::ZeroRotator.Quaternion());
            StartPortal = GetWorld()->SpawnActorDeferred<APortal>(PortalClass, SpawnLocAndRotation);
            StartPortal->NewPosition = RoomSocializer->SpawnPositions->GetComponentLocation() + FVector(-100.f,-100.f,+50.f);
            StartPortal->FinishSpawning(SpawnLocAndRotation);

            RoomSocializer->StartPortalPos = MaxPath[CellIndex]->GetActorLocation();

            break;
    }
    
}

void AMazeManager::SpawnExtraElem(int Index, AMazeCell2* AfterCell, AMazeCell2* BeforeCell) {

    switch(Index){

        //Achiever
        case 0:
            
            if(HatClasses.Num() > 0 && FMath::RandRange(0,9) > 2){

                int NumExtr = FMath::RandRange(0,HatClasses.Num() - 1);
                GetWorld()->SpawnActor<AHat>(HatClasses[NumExtr], AfterCell->GetActorLocation(), FRotator::ZeroRotator);
                HatClasses.RemoveAt(NumExtr);

            }else{

                GetWorld()->SpawnActor<ACoinController>(CoinClass, AfterCell->GetActorLocation(),
                GetDoorRotation(AfterCell,BeforeCell));

            }

            break;
        
        //Killer
        case 1:
            
            GetWorld()->SpawnActor<AHeart>(HeartClass, AfterCell->GetActorLocation(),
                GetDoorRotation(AfterCell,BeforeCell));

            break;

        //Explorer
        case 2:


            GetWorld()->SpawnActor<AStatueInteractElem>(StatueClass, AfterCell->GetActorLocation(),
                GetDoorRotation(AfterCell,BeforeCell));

            break;
        
        //Socializer
        case 3:

            APawnInteractiveClass* Pawn = GetWorld()->SpawnActor<APawnInteractiveClass>(SpokenNpcClass, AfterCell->GetActorLocation(),
                GetDoorRotation(AfterCell,BeforeCell));            
            AddSpeech(Pawn);

            break;

    }
    
}

//Spawn used when there are from 3 to 4 cells free in other paths.
void AMazeManager::SpawnSigleCellElem(int Index, AMazeCell2* CurrentCell) {
    
    IInterfaceMovableAI* Enemy;
    FTransform Transform;

    switch (Index){
    
    //Achiever
    case 0:
    
        GetWorld()->SpawnActor<AAIShooterPawn>(ShooterEnemyClass,CurrentCell->GetActorLocation() , FRotator::ZeroRotator)->bSpawnCoin = true;
        GetWorld()->SpawnActor<AGenericDestructibleElements>(DestrElem,CurrentCell->GetActorLocation() + FVector(-260.f,260.f,-50.f),FRotator::ZeroRotator);
        GetWorld()->SpawnActor<AGenericDestructibleElements>(DestrElem,CurrentCell->GetActorLocation() + FVector(260.f,-260.f,-50.f),FRotator::ZeroRotator);
        GetWorld()->SpawnActor<AGenericDestructibleElements>(DestrElem,CurrentCell->GetActorLocation() + FVector(-260.f,-260.f,-50.f),FRotator::ZeroRotator);
        GetWorld()->SpawnActor<AGenericDestructibleElements>(DestrElem,CurrentCell->GetActorLocation() + FVector(260.f,260.f,-50.f),FRotator::ZeroRotator);

        break;
       
    //Killer
    case 1:

        GetWorld()->SpawnActor<AAIShooterPawn>(ShooterEnemyClass,CurrentCell->GetActorLocation() , FRotator::ZeroRotator);

        break;

    //Explorer
    case 2:

        AddDoubleCircularPatrol(CurrentCell);

        break;

    //Socializer
    case 3:

        Transform.SetLocation(CurrentCell->GetActorLocation());
        Enemy = GetWorld()->SpawnActorDeferred<IInterfaceMovableAI>(MoveAIClass2,Transform);
        Enemy->Positions.Add(CurrentCell->GetActorLocation());
        Cast<APawn>(Enemy)->FinishSpawning(Transform);
        AddSpeech(Cast<APawnInteractiveClass>(Enemy));

        break;

    default:
        break;
    
    }

}

void AMazeManager::PopulateBartle(){

    //Calculate the total number of the cells in a TMap "Type" - Number of cells.
    TMap<Type,int> CellsNumberMap;
    TArray<Type> Keys;
    CalculateTotalNumberOfCells(CellsNumberMap,Keys);

    //Generate Last cell.
    CellsNumberMap.GetKeys(Keys);
    PortalType(Keys[0],MaxPath[MaxPath.Num() - 2]);  

    //Create a Map with all the cells and its relative path.
    TMap<AMazeCell2*, FPath> Cells = CellsToPopulate.MainPath;
    Cells.Append(CellsToPopulate.OtherPaths);
    Cells.Append(CellsToPopulate.ExtrElem);
    Cells.Append(CellsToPopulate.OneCellElem);
    Cells.Append(CellsToPopulate.Door);

    //Assign one Cell in the main path to every Types. (At least you are gonna see all the Types in the main path)
    TArray<AMazeCell2*> TempArray;
    CellsToPopulate.MainPath.GetKeys(TempArray);

    //Just a copy to keep the initial value
    TMap<Type,int> Types = CellsNumberMap;
    
    int Value;
    //If very unlikely to not be verified.
    /*if(CellsToPopulate.MainPath.Num() > 3){

        for(int i = 0; i < Keys.Num(); i++){

            int NumExtr = FMath::RandRange(0,TempArray.Num() - 1);

            //Return the value to be assigned to determine which Type I estracted.
            Value = ReturnTypeValue(Keys[i]);

            //Add one possibile Element. The platfroms have half of the probability.
            if(FMath::RandRange(0,2) < 2)
                AddEnemy(Value, TempArray[NumExtr], CellsToPopulate.MainPath[TempArray[NumExtr]].Path);
            else
                AddFallenPlatforms(Value, TempArray[NumExtr], CellsToPopulate.MainPath[TempArray[NumExtr]].Path);

            Cells.Remove(TempArray[NumExtr]);
            TempArray.RemoveAt(NumExtr);

            //Decrease the value for that Type and if it is 0, remove it.
            Types[Keys[i]] -= 1;

            if(Types[Keys[i]] == 0)
                Types.Remove(Keys[i]);

        }    

    }*/

    int Times = Cells.Num();
    //for the reamins value I assign some cells.
    for(int i = 0; i < Times; i++){

        TArray<Type> TypesKeys;
        Types.GetKeys(TypesKeys); 
        int NumExtr = FMath::RandRange(0, TypesKeys.Num() - 1);
        
        //Return the value to be assigned to determine which Type I estracted.
        Value = ReturnTypeValue(TypesKeys[NumExtr]);

        Types[TypesKeys[NumExtr]] -= 1;

        if(Types[TypesKeys[NumExtr]] == 0)
            Types.Remove(TypesKeys[NumExtr]);

        //Extract one possible cell.
        TArray<AMazeCell2*> KeysCell;
        Cells.GetKeys(KeysCell);
        NumExtr = FMath::RandRange(0, Cells.Num() - 1);
        AMazeCell2* Cell = KeysCell[NumExtr];
        Cells.Remove(Cell);

        if(CellsToPopulate.MainPath.Contains(Cell)){

            if(FMath::RandRange(0,2) < 2)
                AddEnemy(Value, Cell, CellsToPopulate.MainPath[Cell].Path);
            else
                AddFallenPlatforms(Value, Cell, CellsToPopulate.MainPath[Cell].Path);

        }else if(CellsToPopulate.OtherPaths.Contains(Cell)){

            if(FMath::RandRange(0,2) < 2)
                AddEnemy(Value, Cell, CellsToPopulate.OtherPaths[Cell].Path);
            else
                AddFallenPlatforms(Value, Cell, CellsToPopulate.OtherPaths[Cell].Path);

        }else if(CellsToPopulate.Door.Contains(Cell)){

            AddDoor(Value,Cell,CellsToPopulate.Door[Cell].Path); 
            CreateCheckpoint(Cell); 

        }else if(CellsToPopulate.OneCellElem.Contains(Cell)){
            
            SpawnSigleCellElem(Value,Cell);

        }else if(CellsToPopulate.ExtrElem.Contains(Cell)){

            SpawnExtraElem(Value,Cell,CellsToPopulate.Couple[Cell]);
            
        }

    }

}


void AMazeManager::CalculateTotalNumberOfCells(TMap<Type,int>& CellsNumberMap, TArray<Type> Keys){

    int TotalCells = CellsToPopulate.MainPath.Num() +  CellsToPopulate.OtherPaths.Num() +
        CellsToPopulate.OneCellElem.Num() + CellsToPopulate.ExtrElem.Num() + CellsToPopulate.Door.Num();

    TMap<Type,float> CellsPreRounded;
    
    if (USaveGameBartle* LoadedGame = Cast<USaveGameBartle>(UGameplayStatics::LoadGameFromSlot("Bartle", 0))){

        UE_LOG(LogTemp,Warning,TEXT("Values = %f, %f, %f, %f"),  LoadedGame->Achiever, LoadedGame->Killer, LoadedGame->Explorer, LoadedGame->Socializer);

        AGameModeAbstract* GameMode = Cast<AGameModeAbstract>(GetWorld()->GetAuthGameMode());
        GameMode->Update->Types.Add(Type::Achiever, LoadedGame->Achiever);
        GameMode->Update->Types.Add(Type::Killer, LoadedGame->Killer);
        GameMode->Update->Types.Add(Type::Explorer, LoadedGame->Explorer);
        GameMode->Update->Types.Add(Type::Socializer, LoadedGame->Socializer);

        //Create a TMap with all the cells before the round.
        CellsPreRounded = {{Type::Achiever,TotalCells * LoadedGame->Achiever / 200}, {Type::Killer,TotalCells * LoadedGame->Killer / 200},
        {Type::Explorer,TotalCells * LoadedGame->Explorer / 200}, {Type::Socializer,TotalCells * LoadedGame->Socializer / 200}};

    }else{
        
        UE_LOG(LogTemp,Warning,TEXT("Values = %f, %f, %f, %f"), Achiever, Killer, Explorer, Socializer);

        CellsPreRounded = {{Type::Achiever,TotalCells * Achiever / 200}, {Type::Killer,TotalCells * Killer / 200},
        {Type::Explorer,TotalCells * Explorer / 200}, {Type::Socializer,TotalCells * Socializer / 200}};

    }

    CellsPreRounded.ValueSort([](float A, float B) {
        return A > B; // sort keys in reverse
    });

    CellsPreRounded.GetKeys(Keys);

    //Round values to the nearest int.
    CellsNumberMap = 
        {{Keys[0],FGenericPlatformMath::RoundToInt(CellsPreRounded[Keys[0]])},
        {Keys[1],FGenericPlatformMath::RoundToInt(CellsPreRounded[Keys[1]])},
        {Keys[2],FGenericPlatformMath::RoundToInt(CellsPreRounded[Keys[2]])},
        {Keys[3],FGenericPlatformMath::RoundToInt(CellsPreRounded[Keys[3]])}};

    UE_LOG(LogTemp,Warning,TEXT("TotalCells %i"), TotalCells);
    UE_LOG(LogTemp,Warning,TEXT("%i %i"), Keys[0], CellsNumberMap[Keys[0]]);
    UE_LOG(LogTemp,Warning,TEXT("%i %i"), Keys[1], CellsNumberMap[Keys[1]]);
    UE_LOG(LogTemp,Warning,TEXT("%i %i"), Keys[2], CellsNumberMap[Keys[2]]);
    UE_LOG(LogTemp,Warning,TEXT("%i %i"), Keys[3], CellsNumberMap[Keys[3]]);

    //if some value is 0, I eliminated it from the map.
    for(int i = 0; i < 2; i++){

        if(CellsNumberMap[Keys[Keys.Num() - 1 - i]] == 0)
            CellsNumberMap.Remove(Keys[Keys.Num() - 1 - i]);
    
    }

    //Check if after rounding the values, the number are equals.
    CellsNumberMap.GetKeys(Keys);
    int MyCells = 0;
    for(int i = 0; i < Keys.Num(); i++){

        MyCells += CellsNumberMap[Keys[i]];
    
    }

    //if not, subtract or add value starting from the lowest
    if(TotalCells != MyCells){

        int Difference = MyCells - TotalCells;

        if(Difference < 0){

            Difference = FMath::Abs(Difference);

            for(int i = 0; i < Difference; i++){

                CellsNumberMap[Keys[i]] += 1;

            }

        }else{

            for(int i = 0; i < Difference; i++){

                CellsNumberMap[Keys[(Keys.Num() - 1 - i)%Keys.Num()]] -= 1;

            }

        }

    }

    //if some value is 0, I eliminated it from the map.
    for(int i = 0; i < 2; i++){

        if(CellsNumberMap[Keys[Keys.Num() - 1 - i]] == 0)
            CellsNumberMap.Remove(Keys[Keys.Num() - 1 - i]);
    
    }

    //print
    UE_LOG(LogTemp,Warning,TEXT("Post"));    
    for(int i = 0; i < Keys.Num(); i++){
 
        UE_LOG(LogTemp,Warning,TEXT("%i %i"), Keys[i], CellsNumberMap[Keys[i]]);
    
    }

}

//Return the value of the corrisponding type.
int AMazeManager::ReturnTypeValue(int Index){

    switch (Index){

            case Type::Achiever:
                return 0;
        
            case Type::Killer:
                return 1;
        
            case Type::Explorer:
                return 2;
        
            case Type::Socializer:
                return 3;
        
            default:
                return -1;
        }

}


void AMazeManager::CreateCheckpoint(AMazeCell2* Cell){

    FVector Offset;
    ACheckPointLevel1* CheckPoint;

    //create the exact position for the checkpoint.
    if(SetOffsetVector(CellsToPopulate.Couple[Cell], Cell, Offset, 0)){
                
        FRotator Rotator = GetDoorRotation(CellsToPopulate.Couple[Cell], Cell);
        if(Rotator == FRotator(0.f,180.f,0.f))
            Offset = FVector(0.f,100.f,0.f);
        else
            Offset = FVector(0.f,-100.f,0.f);

        CheckPoint = GetWorld()->SpawnActor<ACheckPointLevel1>(CheckPointClass,(CellsToPopulate.Couple[Cell]->GetActorLocation() + Cell->GetActorLocation()) / 2 + Offset,
            GetDoorRotation(CellsToPopulate.Couple[Cell],Cell));

    }else{

        FRotator Rotator = GetDoorRotation(CellsToPopulate.Couple[Cell], Cell);
        if(Rotator == FRotator(0.f,-90.f,0.f))
            Offset = FVector(-100.f,0.f,0.f);
        else
            Offset = FVector(100.f,0.f,0.f);

        CheckPoint = GetWorld()->SpawnActor<ACheckPointLevel1>(CheckPointClass,(CellsToPopulate.Couple[Cell]->GetActorLocation() + Cell->GetActorLocation()) / 2 + Offset,
            GetDoorRotation(CellsToPopulate.Couple[Cell], Cell));
    }

    CheckPoint->MazeManager = this;

}


void AMazeManager::AddSpeech(APawnInteractiveClass* NPC){

    if(BlockedSpeech.Num() == 0){
        BlockedSpeech = OldBlockedSpeech;
        OldBlockedSpeech.Empty();
    }


    //Select a speech.
    int SpeechNumber = FMath::RandRange(0,BlockedSpeech.Num() - 1);
    NPC->Speech = BlockedSpeech[SpeechNumber];
    OldBlockedSpeech.Add(BlockedSpeech[SpeechNumber]);
    BlockedSpeech.RemoveAt(SpeechNumber);

}

#pragma endregion