// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckPointLevel1.h"
#include "../Character/CharacterPawnQuad.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "../Elements/Maze/Maze.h"
#include "EngineUtils.h"
#include "../Elements/Destructible/GenericDestructibleElements.h"
#include "../Elements/GeneralElements/CoinController.h"
#include "../Elements/Hat/Hat.h"
#include "../Obstacle/Trap.h"
#include "../Elements/GeneralElements/Heart.h"
#include "../Elements/Platforms/ShakingFallenPlatform.h"
#include "../Elements/GeneralElements/Doors/Door.h"
#include "../GameManager/MazeManager.h"
#include "../Character/AllyAI/PawnInteractiveClass.h"
#include "../Character/AllyAI/PawnInteractiveMove.h"
#include "../Character/AllyAI/RiddleNPC.h"
#include "../Character/EnemyAI/PatrolAI2.h"
#include "../Character/EnemyAI/AIShooterPawn.h"
#include "../Elements/GeneralElements/Doors/DoorRiddle.h"
#include "../Elements/GeneralElements/Doors/DoorAchiever.h"
#include "../Elements/GeneralElements/Doors/DoorKiller.h"
#include "../Elements/GeneralElements/Doors/DoorExplorer.h"
#include "../Elements/Portal/PortalNight.h"
#include "../Elements/Puzzle/PuzzleButtonPortal.h"
#include "../Elements/Room/RoomKiller.h"
#include "../Elements/Room/RoomSocializer.h"
#include "../Elements/Room/RoomAchiever.h"
#include "../Elements/Room/Room.h"
#include "../Elements/Key/KeyActor.h"
#include "../Elements/Light/CeilingLight.h"
#include "../Elements/FinalLevelActor.h"
#include "../Elements/Storm/Storm.h"
#include "../Elements/Triggers/TriggerMap.h"
#include "../GameModeAbstract.h"
#include "../UI/UIWidgetDialog.h"
 #include "Components/ProgressBar.h"

ACheckPointLevel1::ACheckPointLevel1(){
    
    SpawnPos = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPos"));
	SpawnPos->SetupAttachment(RootComponent);

}

void ACheckPointLevel1::OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit) {

    if(OtherActor->IsA(ACharacterPawnQuad::StaticClass())){

        APawn* MyPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0); 
        Cast<ACharacterPawnQuad>(UGameplayStatics::GetPlayerPawn(GetWorld(),0))->CurrentHealth = Cast<ACharacterPawnQuad>(MyPawn)->MaxHealth;
		
        AGameModeAbstract* GameMode = Cast<AGameModeAbstract>(GetWorld()->GetAuthGameMode());
		UUIWidgetDialog* DialogWidget = Cast<UUIWidgetDialog>(GameMode->GetCurrentWidgetUI());
        if(DialogWidget != nullptr)
		    DialogWidget->HealthBar->SetPercent(1.f);

        if (USaveGameLevel1* SaveGameInstance = Cast<USaveGameLevel1>(UGameplayStatics::CreateSaveGameObject(USaveGameLevel1::StaticClass()))){

            TArray<FGeneralActor> GeneralElem;
            TArray<FMoveActor> MoveElem;
            TArray<FDoorActor> DoorRiddle;
            TArray<FDoorActor> Door;
            TArray<FDoorActor> DoorExplorer;
            TArray<FNightPortal> NightPortals;
            TArray<FDoorAchieverStruct> DoorAchiever;
            TArray<FDoorKillerStruct> DoorKiller;
            TArray<FPuzzlePortalStruct> PuzzlePortals;
            FRoomKillerStruct RoomKiller;
            FRoomAchieverStruct RoomAchiever;
            FTransform Transform;
            
// --- Maze Actor --

            TMap<int, FMazeValue> MazeTransformMap;
            int ActorNumber = 0;
            for (TActorIterator<AMaze> ActorItr(GetWorld()); ActorItr; ++ActorItr){
                
                //Fill up all the value
                FMazeValue T;
                T.TransformsFloor = CreateTransformArray((*ActorItr)->FloorInstances);
                T.TransformsWall = CreateTransformArray((*ActorItr)->WallInstances);
                T.TransformsObstacle = CreateTransformArray((*ActorItr)->ObstacleInstances);
                T.TransformsMetalCrate = CreateTransformArray((*ActorItr)->MetalCrateInstances);
                T.Position = ActorItr->GetActorLocation();

                MazeTransformMap.Add(ActorNumber,T);
                
                ActorNumber += 1;

            }


            SaveGameInstance->MazeTransformMap = MazeTransformMap;

// --- Destructible ---

        TArray<FDestrActor> DestrActors;

        for (TActorIterator<AGenericDestructibleElements> ActorItr(GetWorld()); ActorItr; ++ActorItr){
            
            if(!(*ActorItr)->bIAmDestroyed){
                FDestrActor DestrActor;
                Transform.SetLocation(ActorItr->GetActorLocation());
                Transform.SetRotation(FRotator::ZeroRotator.Quaternion());
                DestrActor.Transform = Transform;
                DestrActor.ActorClass = ActorItr->GetClass();
                DestrActor.ID = (*ActorItr)->ID;
                DestrActor.SpawnActor = (*ActorItr)->SpawnActor;
                
                DestrActors.Add(DestrActor);
            }

        }

        SaveGameInstance->DestructibleElem = DestrActors;

// --- Coins ---

        GeneralElem.Empty();

        for (TActorIterator<ACoinController> ActorItr(GetWorld()); ActorItr; ++ActorItr){
            
            if((*ActorItr)->GetAttachParentActor() == nullptr){
                FGeneralActor GeneralActor;
                Transform.SetLocation(ActorItr->GetActorLocation());
                Transform.SetRotation(FRotator::ZeroRotator.Quaternion());
                GeneralActor.Transform = Transform;
                GeneralActor.ActorClass = ActorItr->GetClass();
                
                GeneralElem.Add(GeneralActor);
            }

        }

        SaveGameInstance->CoinElem = GeneralElem;

// --- Hat ---
        
        GeneralElem.Empty();

        for (TActorIterator<AHat> ActorItr(GetWorld()); ActorItr; ++ActorItr){
            
            FGeneralActor GeneralActor;
            Transform.SetLocation(ActorItr->GetActorLocation());
            Transform.SetRotation(FRotator::ZeroRotator.Quaternion());
            GeneralActor.Transform = Transform;
            GeneralActor.ActorClass = ActorItr->GetClass();
            
            GeneralElem.Add(GeneralActor);

        }

        SaveGameInstance->HatElem = GeneralElem;

// --- TriggerMap ---
        
        GeneralElem.Empty();

        for (TActorIterator<ATriggerMap> ActorItr(GetWorld()); ActorItr; ++ActorItr){
            
            FGeneralActor GeneralActor;
            Transform.SetLocation(ActorItr->GetActorLocation());
            Transform.SetRotation(ActorItr->GetActorRotation().Quaternion());
            GeneralActor.Transform = Transform;
            GeneralActor.ActorClass = ActorItr->GetClass();
            
            GeneralElem.Add(GeneralActor);

        }

        SaveGameInstance->TriggerMaps = GeneralElem;

// --- Trap ---
        
        GeneralElem.Empty();

        for (TActorIterator<ATrap> ActorItr(GetWorld()); ActorItr; ++ActorItr){
            
            FGeneralActor GeneralActor;
            Transform.SetLocation(ActorItr->GetActorLocation());
            Transform.SetRotation(FRotator::ZeroRotator.Quaternion());
            GeneralActor.Transform = Transform;
            GeneralActor.ActorClass = ActorItr->GetClass();
            
            GeneralElem.Add(GeneralActor);

        }

        SaveGameInstance->TrapElem = GeneralElem;

// --- Heart ---
        
        GeneralElem.Empty();

        for (TActorIterator<AHeart> ActorItr(GetWorld()); ActorItr; ++ActorItr){
            
            FGeneralActor GeneralActor;
            Transform.SetLocation(ActorItr->GetActorLocation());
            Transform.SetRotation(FRotator::ZeroRotator.Quaternion());
            GeneralActor.Transform = Transform;
            GeneralActor.ActorClass = ActorItr->GetClass();
            
            GeneralElem.Add(GeneralActor);

        }

        SaveGameInstance->HeartElem = GeneralElem;

// --- Fallen Platforms ---
        
        GeneralElem.Empty();

        for (TActorIterator<AShakingFallenPlatform> ActorItr(GetWorld()); ActorItr; ++ActorItr){
            
            FGeneralActor GeneralActor;
            Transform.SetLocation(ActorItr->GetActorLocation());
            Transform.SetRotation(FRotator::ZeroRotator.Quaternion());
            GeneralActor.Transform = Transform;
            GeneralActor.ActorClass = ActorItr->GetClass();
            
            GeneralElem.Add(GeneralActor);

        }

        SaveGameInstance->FallenPlatformElem = GeneralElem;

// --- Door ---

        Door.Empty();

        for (TActorIterator<ADoor> ActorItr(GetWorld()); ActorItr; ++ActorItr){
            
            if(!ActorItr->IsA(ADoorRiddle::StaticClass()) && !ActorItr->IsA(ADoorExplorer::StaticClass()) &&
                !ActorItr->IsA(ADoorKiller::StaticClass()) && !ActorItr->IsA(ADoorAchiever::StaticClass())){

                FDoorActor GeneralActor;
                Transform.SetLocation(ActorItr->GetActorLocation());
                Transform.SetRotation(ActorItr->GetActorRotation().Quaternion());
                GeneralActor.Transform = Transform;
                GeneralActor.ActorClass = ActorItr->GetClass();

                GeneralActor.bOpenDoor = (*ActorItr)->bOpenDoor;
                GeneralActor.ID = (*ActorItr)->ID;
                
                Door.Add(GeneralActor);
            
            }

        }

        SaveGameInstance->Doors = Door;

// --- Door Riddle ---

        DoorRiddle.Empty();

        for (TActorIterator<ADoorRiddle> ActorItr(GetWorld()); ActorItr; ++ActorItr){
            
            FDoorActor GeneralActor;
            Transform.SetLocation(ActorItr->GetActorLocation());
            Transform.SetRotation(ActorItr->GetActorRotation().Quaternion());
            GeneralActor.Transform = Transform;
            GeneralActor.ActorClass = ActorItr->GetClass();

            GeneralActor.bOpenDoor = (*ActorItr)->bOpenDoor;
            GeneralActor.FinalPosition = (*ActorItr)->FinalPosition;
            GeneralActor.ID = (*ActorItr)->ID;
            
            DoorRiddle.Add(GeneralActor);

        }

        SaveGameInstance->DoorsRiddle = DoorRiddle;

// --- Door Explorer ---

        DoorExplorer.Empty();

        for (TActorIterator<ADoorExplorer> ActorItr(GetWorld()); ActorItr; ++ActorItr){
            
            FDoorActor GeneralActor;
            Transform.SetLocation(ActorItr->GetActorLocation());
            Transform.SetRotation(ActorItr->GetActorRotation().Quaternion());
            GeneralActor.Transform = Transform;
            GeneralActor.ActorClass = ActorItr->GetClass();
                
            GeneralActor.bOpenDoor = (*ActorItr)->bOpenDoor;
            GeneralActor.FinalPosition = (*ActorItr)->FinalPosition;
            GeneralActor.ID = (*ActorItr)->ID;
            
            DoorExplorer.Add(GeneralActor);

        }

        SaveGameInstance->DoorsExplorer = DoorExplorer;


// --- Door Achiever ---

        DoorAchiever.Empty();

        for (TActorIterator<ADoorAchiever> ActorItr(GetWorld()); ActorItr; ++ActorItr){
            
            FDoorAchieverStruct GeneralActor;
            Transform.SetLocation(ActorItr->GetActorLocation());
            Transform.SetRotation(ActorItr->GetActorRotation().Quaternion());
            GeneralActor.Transform = Transform;
            GeneralActor.ActorClass = ActorItr->GetClass();

            GeneralActor.bOpenDoor = (*ActorItr)->bOpenDoor;
            GeneralActor.FinalPosition = (*ActorItr)->FinalPosition;
            GeneralActor.ID = (*ActorItr)->ID;
            
            GeneralActor.KeyPos = (*ActorItr)->KeyPosition;

            TArray<int> IDs;
            for(int i = 0; i < (*ActorItr)->DestrActors.Num(); i++){

                IDs.Add((*ActorItr)->DestrActors[i]->ID);

                if((*ActorItr)->DestrActors[i]->SpawnActor == (*ActorItr)->KeyClass)
                    GeneralActor.IDKey = (*ActorItr)->DestrActors[i]->ID;
                

            }
            
            GeneralActor.IDs = IDs;

            DoorAchiever.Add(GeneralActor);

        }

        SaveGameInstance->DoorsAchiever = DoorAchiever;

// --- Door Killer ---

        DoorKiller.Empty();

        for (TActorIterator<ADoorKiller> ActorItr(GetWorld()); ActorItr; ++ActorItr){
            
                FDoorKillerStruct GeneralActor;
                Transform.SetLocation(ActorItr->GetActorLocation());
                Transform.SetRotation(ActorItr->GetActorRotation().Quaternion());
                GeneralActor.Transform = Transform;
                GeneralActor.ActorClass = ActorItr->GetClass();
                GeneralActor.ID = (*ActorItr)->ID;

                TArray<int> IDs;
                for(AEnemyAIAbstract* Enemy : (*ActorItr)->Enemies)
                    IDs.Add(Enemy->IDEnemy);

                GeneralActor.IDs = IDs;

                GeneralActor.bOpenDoor = (*ActorItr)->bOpenDoor;
                GeneralActor.FinalPosition = (*ActorItr)->FinalPosition;
                
                DoorKiller.Add(GeneralActor);

        }

        SaveGameInstance->DoorsKiller = DoorKiller;

// --- Enemy ---
        
        GeneralElem.Empty();

        for (TActorIterator<AEnemyAIAbstract> ActorItr(GetWorld()); ActorItr; ++ActorItr){
            
            if((*ActorItr)->GetAttachParentActor() == nullptr){
            
                AActor* Parent = ActorItr->GetAttachParentActor();

                FGeneralActor GeneralActor;
                Transform.SetLocation((*ActorItr)->InitialPos);
                Transform.SetRotation(ActorItr->GetActorRotation().Quaternion());
                GeneralActor.Transform = Transform;
                GeneralActor.ActorClass = ActorItr->GetClass();
                GeneralActor.ID = (*ActorItr)->IDEnemy;
                GeneralActor.bSpawnCoin = (*ActorItr)->bSpawnCoin;
                    
                GeneralElem.Add(GeneralActor);
            
            }

        }

        SaveGameInstance->Enemies = GeneralElem;

// --- Allies NPC ---
        
        GeneralElem.Empty();

        for (TActorIterator<APawnInteractiveClass> ActorItr(GetWorld()); ActorItr; ++ActorItr){
            
            if(!ActorItr->IsA(ARiddleNPC::StaticClass()) && !ActorItr->IsA(APawnInteractiveMove::StaticClass())){
            
                FGeneralActor GeneralActor;
                Transform.SetLocation(ActorItr->GetActorLocation());
                Transform.SetRotation(ActorItr->GetActorRotation().Quaternion());
                GeneralActor.Transform = Transform;
                GeneralActor.ActorClass = ActorItr->GetClass();
                GeneralActor.QuestionAt = (*ActorItr)->QuestionAt;
                GeneralActor.bAlreadySpoken = (*ActorItr)->bAlreadySpoken;
                GeneralActor.Speech = (*ActorItr)->Speech;  
                GeneralActor.ID = (*ActorItr)->ID;
                GeneralElem.Add(GeneralActor);
            
            }

        }

        SaveGameInstance->Allies = GeneralElem;

// --- Patrols NPC ---
        
        MoveElem.Empty();

        for (TActorIterator<APatrolAI2> ActorItr(GetWorld()); ActorItr; ++ActorItr){
            
            AActor* Parent = ActorItr->GetAttachParentActor();
            if(ActorItr->GetAttachParentActor() == nullptr){
                
                FMoveActor MoveActor;
                Transform.SetLocation((*ActorItr)->InitialPos);
                Transform.SetRotation(ActorItr->GetActorRotation().Quaternion());
                MoveActor.Transform = Transform;
                MoveActor.ActorClass = ActorItr->GetClass();
                MoveActor.Positions = (*ActorItr)->Positions;
                MoveActor.StartIndex = (*ActorItr)->StartIndex;
                MoveActor.StartDirection = (*ActorItr)->StartDirection;
                
                MoveElem.Add(MoveActor);
            
            }

        }

        SaveGameInstance->Patrols = MoveElem;

// --- Move Ally ---

        MoveElem.Empty();

        for (TActorIterator<APawnInteractiveMove> ActorItr(GetWorld()); ActorItr; ++ActorItr){
            
            AActor* Parent = ActorItr->GetAttachParentActor();
            if(ActorItr->GetAttachParentActor() == nullptr){
                
                FMoveActor MoveActor;
                Transform.SetLocation(ActorItr->GetActorLocation());
                Transform.SetRotation(ActorItr->GetActorRotation().Quaternion());
                MoveActor.Transform = Transform;
                MoveActor.ActorClass = ActorItr->GetClass();
                MoveActor.Positions = (*ActorItr)->Positions;           
                MoveActor.QuestionAt = (*ActorItr)->QuestionAt;
                MoveActor.bAlreadySpoken = (*ActorItr)->bAlreadySpoken;
                MoveActor.Speech = (*ActorItr)->Speech;
                
                
                MoveElem.Add(MoveActor);
            
            }

        }

        SaveGameInstance->MoveAllies = MoveElem;

// --- Checkpoints ---
        
        GeneralElem.Empty();

        for (TActorIterator<ACheckPointLevel1> ActorItr(GetWorld()); ActorItr; ++ActorItr){
            
            FGeneralActor GeneralActor;
            Transform.SetLocation(ActorItr->GetActorLocation());
            Transform.SetRotation(ActorItr->GetActorRotation().Quaternion());
            GeneralActor.Transform = Transform;
            GeneralActor.ActorClass = ActorItr->GetClass();
            
            GeneralElem.Add(GeneralActor);

        }

        SaveGameInstance->Checkpoints = GeneralElem;

//Last Actor

        for (TActorIterator<AFinalLevelActor> ActorItr(GetWorld()); ActorItr; ++ActorItr){
            
            FGeneralActor GeneralActor;
            Transform.SetLocation(ActorItr->GetActorLocation());
            Transform.SetRotation(ActorItr->GetActorRotation().Quaternion());
            GeneralActor.Transform = Transform;
            GeneralActor.ActorClass = ActorItr->GetClass();

            SaveGameInstance->LastActor = GeneralActor;

        }

//Storms

        MoveElem.Empty();

        for (TActorIterator<AStorm> ActorItr(GetWorld()); ActorItr; ++ActorItr){
            
            FMoveActor MoveActor;
            Transform.SetLocation(ActorItr->GetActorLocation());
            Transform.SetRotation(ActorItr->GetActorRotation().Quaternion());
            MoveActor.Positions = (*ActorItr)->Positions;      
            MoveActor.Transform = Transform;
            MoveActor.ActorClass = ActorItr->GetClass();
            
            MoveElem.Add(MoveActor);

        }

        SaveGameInstance->Storms = MoveElem;

// --- Ceiling ---

      /*  GeneralElem.Empty();

        for (TActorIterator<ACeilingLight> ActorItr(GetWorld()); ActorItr; ++ActorItr){
            
            FGeneralActor GeneralActor;
            Transform.SetLocation(ActorItr->GetActorLocation());
            Transform.SetRotation(ActorItr->GetActorRotation().Quaternion());
            GeneralActor.Transform = Transform;
            GeneralActor.ActorClass = ActorItr->GetClass();
            
            GeneralElem.Add(GeneralActor);

        }

        SaveGameInstance->Lights = GeneralElem;*/

// --- Night Portal ---
        
        NightPortals.Empty();

        for (TActorIterator<APortal> ActorItr(GetWorld()); ActorItr; ++ActorItr){
            
            FNightPortal NightPortal;
            Transform.SetLocation(ActorItr->GetActorLocation());
            Transform.SetRotation(ActorItr->GetActorRotation().Quaternion());
            NightPortal.Transform = Transform;
            NightPortal.ActorClass = ActorItr->GetClass();
            NightPortal.NewPosition = (*ActorItr)->NewPosition;
            
            NightPortals.Add(NightPortal);

        }

        SaveGameInstance->NightPortals = NightPortals;

// --- PuzzlePortal ---
        
        PuzzlePortals.Empty();

        for (TActorIterator<APuzzleButtonPortal> ActorItr(GetWorld()); ActorItr; ++ActorItr){
            
            FPuzzlePortalStruct PuzzlePortal;
            Transform.SetLocation(ActorItr->GetActorLocation());
            Transform.SetRotation(ActorItr->GetActorRotation().Quaternion());
            PuzzlePortal.Transform = Transform;
            PuzzlePortal.ActorClass = ActorItr->GetClass();
            PuzzlePortal.EndSpawnPosition = (*ActorItr)->EndSpawnPosition;
            PuzzlePortal.DoorID = (*ActorItr)->Door->ID;
            
            PuzzlePortals.Add(PuzzlePortal);

        }

        SaveGameInstance->PuzzlePortals = PuzzlePortals;

// --- Room Killer / Socializer---

        for (TActorIterator<ARoomKiller> ActorItr(GetWorld()); ActorItr; ++ActorItr){
            
            Transform.SetLocation(ActorItr->GetActorLocation());
            Transform.SetRotation(ActorItr->GetActorRotation().Quaternion());
            RoomKiller.Transform = Transform;
            RoomKiller.ActorClass = ActorItr->GetClass();
            RoomKiller.StartPortalPos = (*ActorItr)->StartPortalPos;
            RoomKiller.DoorID = (*ActorItr)->Door->ID;
            RoomKiller.NPCID = (*ActorItr)->InteractiveActor->ID;

        }

        SaveGameInstance->RoomKillerStruct = RoomKiller;

// --- Room Achiever ---

        for (TActorIterator<ARoomAchiever> ActorItr(GetWorld()); ActorItr; ++ActorItr){
            
            Transform.SetLocation(ActorItr->GetActorLocation());
            Transform.SetRotation(ActorItr->GetActorRotation().Quaternion());
            RoomAchiever.Transform = Transform;
            RoomAchiever.ActorClass = ActorItr->GetClass();
            RoomAchiever.EndPos = (*ActorItr)->EndPos;
            RoomAchiever.DoorID = (*ActorItr)->Door->ID;

            for(int i = 0; i < (*ActorItr)->Shooters.Num(); i++)
                RoomAchiever.EnemiesID.Add((*ActorItr)->Shooters[i]->IDEnemy);

        }

        SaveGameInstance->RoomAchieverStruct = RoomAchiever;

// --- Player ---

        SaveGameInstance->PlayerPos = SpawnPos->GetComponentLocation();
        SaveGameInstance->PlayerRot = UKismetMathLibrary::FindLookAtRotation(SpawnPos->GetComponentLocation(),GetActorLocation());
        SaveGameInstance->PlayerProjectileTimeout = Cast<ACharacterPawnQuad>(OtherActor)->ProjectileTimeout;

        if(Cast<ACharacterPawnQuad>(OtherActor)->EquipmentMesh->GetStaticMesh() != nullptr){
        
            SaveGameInstance->PlayerHat = true;
            SaveGameInstance->HatsID = Cast<ACharacterPawnQuad>(OtherActor)->HatsOwned;
            SaveGameInstance->CurrentHatMaterial = Cast<ACharacterPawnQuad>(OtherActor)->CurrentHatMaterial;

        }

// --- Speech ---

        SaveGameInstance->Speech = CreateSpeech(MazeManager->Speech);
        SaveGameInstance->Questions = CreateSpeech(MazeManager->Questions);
        SaveGameInstance->BlockedSpeech = CreateSpeech(MazeManager->BlockedSpeech);
        SaveGameInstance->OldSpeech = CreateSpeech(MazeManager->OldSpeech);
        SaveGameInstance->OldQuestions = CreateSpeech(MazeManager->OldQuestions);
        SaveGameInstance->OldBlockedSpeech = CreateSpeech(MazeManager->OldBlockedSpeech);

// --- Other ---
        SaveGameInstance->DestrID = AGenericDestructibleElements::IDCounter;
        SaveGameInstance->EnemyID = AEnemyAIAbstract::IDCounter;        
        SaveGameInstance->AllyID = APawnInteractiveClass::IDCount;

        SaveGameInstance->Coins = GameMode->GetCoins();
        SaveGameInstance->EnemiesDefeated = GameMode->GetEnemies();
        SaveGameInstance->SpokenAllies = GameMode->GetAllies();
        SaveGameInstance->MapVisited = GameMode->GetMap();

        SaveGameInstance->TotalCoins = GameMode->TotalCoins;
        SaveGameInstance->TotalEnemiesDefeated = GameMode->TotalEnemies;
        SaveGameInstance->TotalSpokenAllies = GameMode->TotalAllies;
        SaveGameInstance->TotalMap = GameMode->TotalMap;

        // Start async save process.;
		UGameplayStatics::AsyncSaveGameToSlot(SaveGameInstance, "CheckpointLevel1", 0);

        }

    } 

}

//Create an array with the trasfomr of instanced mesh from the maze.
TArray<FTransform> ACheckPointLevel1::CreateTransformArray(UInstancedStaticMeshComponent* MeshInstances) {

    TArray<FTransform> Instance;
    for(int i = 0; i < MeshInstances->GetInstanceCount(); i++){

        FTransform Transform;
        MeshInstances->GetInstanceTransform(i,Transform);
        Instance.Add(Transform);

    } 
    
    return Instance;

}

//Convert an Array<Array<FString>> to TArray<FSpeech> (Nested loop are not permitted)
TArray<FSpeech> ACheckPointLevel1::CreateSpeech(TArray<TArray<FString>> List) {

    TArray<FSpeech> StringArray;
    for(int i = 0; i < List.Num(); i++){

        FSpeech Speech;
        Speech.String =  List[i];
        StringArray.Add(Speech);

    }

    return StringArray;

}