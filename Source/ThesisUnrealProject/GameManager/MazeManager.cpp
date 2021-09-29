// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeManager.h"
#include "Containers/Array.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "MazeCell2.h"
#include "RoomMaze.h"
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
#include "../Elements/Room/ArenaEnemies/ArenaEnemies.h"
#include "../Elements/Room/RumbleArena/RumbleArenaDoorNpc.h"
#include "../Elements/Room/UndergroundRoom/MazeArena/MazeArena.h"
#include "../Elements/Room/UndergroundRoom/RiddleArena/RiddleArena.h"
#include "../Elements/Triggers/Trigger.h"
#include "../Elements/Triggers/TriggerSpawnNight.h"
#include "../Elements/Stairs/Stair.h"
#include "../Character/EnemyAI/AIBull.h"
#include "../Character/EnemyAI/AIShooterPawn.h"
#include "../Character/EnemyAI/PatrolAIPawn.h"
#include "../Character/AllyAI/PawnInteractiveClass.h"
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
    
    StandardMazeCreation();

    DepthVisit(MazeGraph->GetCurrentNode());

    if(PopulateMaze){
        
        //AddDoors(1);

        GenerateElements(MaxPath);

        GenerateDoors();

        //PopulateOtherPath();

        Populate(MaxPath);

    }

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
    CreateRooms(3);
    CreateMaze(MazeGraph->GetCurrentNode(),nullptr);
    //PrintMaze();
}


//Used to draw the line for the visual graph
void AMazeManager::PrintMaze(TArray<AMazeCell2*> Nodes, FColor Color) {

    /*for (AMazeCell2* Cell : Nodes) {
		for(Side<AMazeCell2>* Edge: MazeGraph->GetSides(Cell)){
			3
		}
    }*/

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
            MazeActor->CreateFloor(Transform);
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

//Create the rooms based on the size passed by parameter.
void AMazeManager::CreateRooms(int RoomSize) {
    
    for(int k = 0; k < MazeRooms; k++){

        TArray<AMazeCell2*> Cells = MazeGraph->GetNodes();
        int NumExtr;
        
        do{

            NumExtr = FMath::RandRange(Length,Cells.Num() - Length * RoomSize);

        //Check if I am in the first column and then check if there are at least 4 cells free.
        }while(CheckRoomIntersection(Cells,NumExtr));

        for(int i = 0; i < RoomSize; i++){

            for(int j = 0; j < RoomSize; j++){

                Cells[Length *i + NumExtr + j]->bIsRoom = true;
                Cells[Length *i + NumExtr + j]->RoomNumber = k;
                
                if(j != RoomSize - 1){
                
                    Cells[Length *i + NumExtr + j]->DestroyWall(Cells[Length * i + NumExtr + j + 1]);
                    MazeGraph->DeleteSide(Cells[Length *i + NumExtr + j],Cells[Length * i + NumExtr + j + 1]);

                }

                if(i != RoomSize - 1){

                    Cells[Length *i + NumExtr + j]->DestroyWall(Cells[Length * (i + 1) + NumExtr + j]);
                    MazeGraph->DeleteSide(Cells[Length *i + NumExtr + j],Cells[Length * (i + 1) + NumExtr + j]);

                }

                Cells[Length *i + NumExtr + j]->DestroyFloor();
                
                if(RoomSize * i + j == (int)((RoomSize * RoomSize) / 2)){
                    
                    RoomCenter.Add(k,Cells[Length *i + NumExtr + j]->GetActorLocation());
                    RoomCenter[k].Z = -70.f;

                }

            }   

        }
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

//First I check If it is in the first column, then if there are at least 4 cells empty in the end. Finally I check the sourrindings cells.
bool AMazeManager::CheckRoomIntersection(TArray<AMazeCell2*> Cells, int NumExtr) {

    if(NumExtr % Length == 0)
        return true;
        
    int a = (int)(NumExtr / Length + 1) * Length - NumExtr;

    if((int)(NumExtr / Length + 1) * Length - NumExtr < 4)
        return true;

    int Start = NumExtr - Length - 1;

    for(int i = 0; i < 5; i++){

        for(int j = 0; j < 5; j++){

            if(Cells[Length * i + Start + j]->bIsRoom)
                return true;

        }

    }

    return false;

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

                    if(MazeCellMax.Num() > 4){
                        
                        GenerateElements(MazeCellMax);

                        SpawnExtraElem(3,MazeCellMax[MazeCellMax.Num() - 1],MazeCellMax[MazeCellMax.Num() - 2]);
                        
                    }else{

                        if(MazeCellMax.Num() > 1)
                            SpawnExtraElem(3,MazeCellMax[MazeCellMax.Num() - 1],MazeCellMax[MazeCellMax.Num() - 2]);
                        else
                            SpawnExtraElem(3,MazeCellMax[MazeCellMax.Num() - 1],Path[i]);

                    }

                    Populate(MazeCellMax);

                }

            }


        }

    }

}

void AMazeManager::LoadFromFile(TArray<TArray<FString>>& List, FString FileName) {
    
    TArray<FString> StringArray;
    FString CompleteFilePath = FPaths::GameSourceDir() + "ThesisUnrealProject/TextFiles/" + FileName +".txt"; 
    FFileHelper::LoadFileToStringArray(StringArray,*CompleteFilePath);

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

    //PrintMaze(MaxPath, FColor(0.f,0.f,0.f));

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

void AMazeManager::SetDynamicVisitedToZero() {
    
    /*for(AMazeCell* Cell: OldPath)
    	Cell->bDynamicIsVisited = false;*/

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
    
    //The process is divided in 3 parts. First check if I am in a crossroad.
    /*if(!MaxPath.Contains(Current) && Sides.Num() > 2){
        
        if(!(*NewPath).Contains(Current))
            (*NewPath).Add(Current);

        
        TArray<AMazeCell2*>* Node = new TArray<AMazeCell2*>(*NewPath);
        
        if(!OtherGraph->Contains(Node)){
            OtherGraph->AddNode(Node);

            if(CurrentNode != nullptr)

                OtherGraph->AddSide(CurrentNode,Node,0.f);

        }
        
        (*NewPath).Empty();

        for(Side<AMazeCell2>* S: Sides){
                
            if(!(*NewPath).Contains(Current))
                (*NewPath).Add(Current);

            if(S->To != MaxPath[MaxPathIndex + 1] && S->To != Previous){

                CreateOtherPaths(NewPath, S->To,Current, MaxPathIndex,OtherGraph,Node);

            }

        }

    //the if it is at the end of the street
    }if(Sides.Num() == 1){

        if(!(*NewPath).Contains(Current))
            (*NewPath).Add(Current);

        if(!Current->bIsRoom || Previous != MaxPath[MaxPathIndex]){

            if((*NewPath).Num() > 1){
            
                TArray<AMazeCell2*>* Node = new TArray<AMazeCell2*>(*NewPath);

                if(!OtherGraph->Contains(Node)){
                    OtherGraph->AddNode(Node);

                    if(CurrentNode != nullptr)

                        OtherGraph->AddSide(CurrentNode,Node,0.f);

                }
            
            }

            (*NewPath).Empty();

        }

    //Any ohter cases.
    }else{
        
        for(Side<AMazeCell2>* S: Sides){
                
            if(!(*NewPath).Contains(Current))
                (*NewPath).Add(Current);

            if(S->To != MaxPath[MaxPathIndex + 1] && S->To != Previous){

                CreateOtherPaths(NewPath, S->To,Current, MaxPathIndex,OtherGraph,CurrentNode);

            }

        }

    }

    (*NewPath).Empty();

    //If I am in maxpath I proceed along the maxpth path.
    if(MaxPathIndex + 1 < MaxPath.Num() && MaxPath[MaxPathIndex] == Current){
        
        if(OtherGraph->GetNodes().Num() != 0){
            OtherPaths.Add((*OtherGraph));
            OtherGraph->DeleteAll();
        }
        CreateOtherPaths(NewPath, MaxPath[MaxPathIndex+1],Current, MaxPathIndex+1,OtherGraph,CurrentNode);


    }*/

}

void AMazeManager::AddDoors(int Index) {

    for(Side<AMazeCell2>* Sides: MazeGraph->GetSides(MaxPath[Index])){
		
		if(Sides->To->RoomNumber != -1){
			
			if(Index + 1 < MaxPath.Num()){

                FVector Pos = (MaxPath[Index + 1]->GetActorLocation() + MaxPath[Index]->GetActorLocation()) / 2.f;
                Pos.Z = 200.f;
                FRotator Rot;

                if(MaxPath[Index]->GetActorLocation().Y == MaxPath[Index + 1]->GetActorLocation().Y)
                    Rot = FRotator(0.f,90.f,0.f);
                else
                    Rot = FRotator(0.f,0.f,0.f);
                

                //Spawn the doors
				ADoor* Door = GetWorld()->SpawnActor<ADoor>(DoorClass,Pos,Rot);
                Door->SetActorScale3D(FVector(1.7f,3.f,0.75f));

                if(MaxPath[Index]->GetActorLocation().Y == Sides->To->GetActorLocation().Y)
                    Rot = FRotator(0.f,90.f,0.f);
                else
                    Rot = FRotator(0.f,0.f,0.f);

                Pos =  (Sides->To->GetActorLocation() + MaxPath[Index]->GetActorLocation()) / 2.f;
                Pos.Z = 500.f;
                ADoor* RoomDoor = GetWorld()->SpawnActor<ADoor>(DoorClass,Pos,Rot);
                RoomDoor->SetActorScale3D(FVector(1.7f,3.f,0.75f));
                RoomDoor->SetDoorDirection(true);

                AddRoom(2,Door,RoomDoor,RoomCenter[Sides->To->RoomNumber],Sides->To); //FMath::RandRange(0,3)

			}

		}

	}

    if(Index + 1 < MaxPath.Num()){
        AddDoors(++Index);
    }
    
}

void AMazeManager::AddRoom(int Index, ADoor* Door, ADoor* RoomDoor, FVector Pos, AMazeCell2* RoomCell) {

    //Collected all the variable at the beginning because it gives me error if create a variable half way.
    AGeneralRoomWithDoor* Arena;
    FVector Location;
    ATrigger* Trigger;
    FVector MazeLocation;
    FVector DoorPos;
    int ExtrNum;
    
    FTransform ArenaLocAndRotation;
    ArenaLocAndRotation.SetLocation(Pos);
    ArenaLocAndRotation.SetRotation(FRotator::ZeroRotator.Quaternion()); 

    switch(Index){

        case 0:

            Arena = GetWorld()->SpawnActor<AArenaEnemies>(EnemiesArenaClass,Pos,FRotator::ZeroRotator);
            Arena->Door = Door;
            
            Location = RoomDoor->GetActorLocation();
            Location.Z = 150.f;
            Trigger = GetWorld()->SpawnActor<ATrigger>(TriggerClass,Location ,RoomDoor->GetActorRotation()); 
		    Trigger->ChangeVisibility(true);
            Trigger->SetActorScale3D(FVector(1.f,1.5f,2.f));

            break;
        
        case 1:
        
            Arena = GetWorld()->SpawnActor<ARumbleArenaDoorNpc>(RumbleArenaClass,Pos,FRotator::ZeroRotator);
            Arena->Door = Door;
            Cast<ARumbleArenaDoorNpc>(Arena)->RoomDoor = RoomDoor;

            break;

        case 2:

            Arena = GetWorld()->SpawnActorDeferred<AMazeArena>(MazeArenaClass, ArenaLocAndRotation);
            Arena->Door = Door;
            ExtrNum = FMath::RandRange(0,ArenaSpawnLocation.Num()-1);
            Cast<AMazeArena>(Arena)->PortalPosition = ArenaSpawnLocation[ExtrNum];
            ArenaSpawnLocation.RemoveAt(ExtrNum);
            Arena->FinishSpawning(ArenaLocAndRotation);

            break;

        case 3:

            Arena = GetWorld()->SpawnActorDeferred<ARiddleArena>(RiddleArenaClass, ArenaLocAndRotation);
            ARiddleArena* CastedArena = Cast<ARiddleArena>(Arena);
            CastedArena->Door = Door;
            CastedArena->Questions = &Questions;
            CastedArena->OldQuestions = &OldQuestions;
            CastedArena->Speech = &Speech;
            CastedArena->OldSpeech = &OldSpeech;
            CastedArena->BlockedSpeech = &BlockedSpeech;
            CastedArena->OldBlockedSpeech = &OldBlockedSpeech;
            
            ExtrNum = FMath::RandRange(0,ArenaSpawnLocation.Num()-1);
            CastedArena->PortalPosition = ArenaSpawnLocation[ExtrNum];
            ArenaSpawnLocation.RemoveAt(ExtrNum);

            Arena->FinishSpawning(ArenaLocAndRotation);

            CastedArena->GenerateRiddleDoors();
            break;
    }

}

void AMazeManager::GenerateElements(TArray<AMazeCell2*> Path) {
    
    for(int i = 2; i < Path.Num() - 2; i += 4){ //MaxPath.Num() - 2

        if(i == 2 || (i - 2) % 10 != 0){
        
            //AddEnemy(FMath::RandRange(0,3), MaxPath[i - 1]); //FMath::RandRange(0,3)
            if(FMath::RandRange(0,2) < 2)
                AddEnemy(FMath::RandRange(0,3), Path[i - 1], Path);
            else
                AddFallenPlatforms(FMath::RandRange(0,3), Path[i - 1], Path);
        
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
        
        TypeOfPatrols(FMath::RandRange(0,2),CellIndex, Path); //FMath::RandRange(0,1)

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
void AMazeManager::GenerateDecorations(FVector StartPos, FVector EndPos, FVector EndLineTracingPos, bool Spawn,TSubclassOf<AGeneralElem> SpawnActor) {
    
    FTransform Transform;
    Transform.SetRotation(FRotator::ZeroRotator.Quaternion());
    
    FHitResult Hit;

    LineTracing(Hit,StartPos,EndLineTracingPos);
    if(Hit.GetActor() != nullptr){
        Transform.SetLocation(EndPos);
        if(!Spawn)
            MazeActor->CreateObstacle(Transform);
        else
            GetWorld()->SpawnActor<AGeneralElem>(SpawnActor,Transform);      
        
    }

}

void AMazeManager::TypeOfPatrols(int Index, int CellIndex, TArray<AMazeCell2*> Path) {
    
    IInterfaceMovableAI* Enemy;
    FVector Offset;
    FVector LastOffset;
    FTransform Transform;
    
    switch (Index){

    case 0:
        //Here I create the enemy
        Enemy = GetWorld()->SpawnActor<IInterfaceMovableAI>(PatrolEnemyClass,Path[CellIndex]->GetActorLocation(), FRotator::ZeroRotator);

        /*for the number of cells I consider (This case 3), I check the position beetween the current Cell and the next one,
        and generate one obstacle in near the center of the cell and in the middle between two cells. (If I create an obstacle
        where there is not a wall, I delete it.)*/
        for(int i = 0; i< 3; i++){

            Enemy->Positions.Add(Path[CellIndex + i]->GetActorLocation());

            GenerateSideElements(CellIndex,i, MazeActor->ObstacleHeight, -25.f, 320.f, false, nullptr, Path);

        }
        
        //Set the initial value of the BTree.
        Enemy->SetInitialValue(Cast<APawn>(Enemy)->GetActorLocation(),0,true, true);

        break;

    case 1:

        GenerateSideActor(PatrolEnemyClass,CellIndex,Path);
        break;

    case 2:

        //Create the patrols for the first and the third cell.
        for(int i = 0; i< 3; i += 2){

            //Here I create the enemy
            Enemy = GetWorld()->SpawnActor<IInterfaceMovableAI>(PatrolEnemyClass,Path[CellIndex + i]->GetActorLocation(), FRotator::ZeroRotator);

            SetOffsetVector(Path[CellIndex + 1 + i],Path[CellIndex + i],Offset,350);

            Enemy->Positions.Add(Path[CellIndex + i]->GetActorLocation() + Offset);
            Enemy->Positions.Add(Path[CellIndex + i]->GetActorLocation() - Offset);

            //Set the initial value of the BTree.
            Enemy->SetInitialValue(Cast<APawn>(Enemy)->GetActorLocation(),0,true, true);
        
        }

        Transform.SetRotation(FRotator::ZeroRotator.Quaternion());
        Transform.SetLocation(Path[CellIndex + 1]->GetActorLocation());
        MazeActor->CreateObstacle(Transform);

        //Create 2 patrols for the second cell (Circular movement) in the opposite way.
        for(int i = 0; i < 2; i ++){

            //Here I create the enemy
            if(i == 0)
                Enemy = GetWorld()->SpawnActor<IInterfaceMovableAI>(PatrolEnemyCircularClass,Path[CellIndex + 1]->GetActorLocation() + FVector(300.f,300.f,0.f), FRotator::ZeroRotator);
            else
                Enemy = GetWorld()->SpawnActor<IInterfaceMovableAI>(PatrolEnemyCircularClass,Path[CellIndex + 1]->GetActorLocation() + FVector(-300.f,-300.f,0.f), FRotator::ZeroRotator);

            Enemy->Positions.Add(Path[CellIndex + 1]->GetActorLocation() + FVector(300.f,300.f,0.f));
            Enemy->Positions.Add(Path[CellIndex + 1]->GetActorLocation() + FVector(-300.f,300.f,0.f));
            Enemy->Positions.Add(Path[CellIndex + 1]->GetActorLocation() + FVector(-300.f,-300.f,0.f));
            Enemy->Positions.Add(Path[CellIndex + 1]->GetActorLocation() + FVector(300.f,-300.f,0.f));

            //Set the initial value of the BTree.
            if(i == 0)
                Enemy->SetInitialValue(Cast<APawn>(Enemy)->GetActorLocation(),0,true, false);
            else
                Enemy->SetInitialValue(Cast<APawn>(Enemy)->GetActorLocation(),2,true, false);

        }
        
        break;

    default:
        UE_LOG(LogTemp,Warning,TEXT("TypeOfPatrols"));
        break;

    }

    

}

void AMazeManager::TypeOfMoveAlly(int Index, int CellIndex, TArray<AMazeCell2*> Path) {
    
    IInterfaceMovableAI* Enemy;
    FTransform Transform;

    switch (Index){

    case 0:
        
        for(int i = 0; i < 3; i++){
            Enemy = GetWorld()->SpawnActor<IInterfaceMovableAI>(MoveAIClass2,Path[CellIndex + i]->GetActorLocation(), FRotator::ZeroRotator);
            Enemy->SetInitialValue(Path[CellIndex + i]->GetActorLocation(),1,true, true);
        }

        break;

    case 1:

        GenerateSideActor(MoveAIClass,CellIndex, Path);
        
        break;

    case 2:

        Enemy = GetWorld()->SpawnActor<IInterfaceMovableAI>(MoveAIClass2,(Path[CellIndex + 1]->GetActorLocation() + Path[CellIndex + 2]->GetActorLocation())/2, FRotator::ZeroRotator);
        Enemy->SetInitialValue((Path[CellIndex + 1]->GetActorLocation() + Path[CellIndex + 2]->GetActorLocation())/2,1,true, true);
        
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
void AMazeManager::GenerateSideActor(TSubclassOf<APawn> AIClass, int CellIndex, TArray<AMazeCell2*> Path) {
        
        IInterfaceMovableAI* Enemy;
        IInterfaceMovableAI* SecondEnemy;
        FVector Offset;
        FVector LastOffset;
        FTransform Transform;

        //Generate an Offset based on the position of two cells.
        SetOffsetVector(MaxPath[CellIndex + 1],Path[CellIndex],Offset,220.f);

        //Generate two enemies.
        Enemy = GetWorld()->SpawnActor<IInterfaceMovableAI>(AIClass,Path[CellIndex]->GetActorLocation() + Offset, FRotator::ZeroRotator);
        SecondEnemy = GetWorld()->SpawnActor<IInterfaceMovableAI>(AIClass,Path[CellIndex]->GetActorLocation() - Offset, FRotator::ZeroRotator);

        /*for the number of cells I consider (This case 3), I assign the new position to the patrol's array. The offset is used
        to arrange the position.*/
        for(int i = 0; i < 3; i++){
            LastOffset = Offset;

            SetOffsetVector(Path[CellIndex + 1 + i],Path[CellIndex + i],Offset,220.f);
            if(LastOffset != Offset){

                Enemy->Positions.Add(Path[CellIndex + i]->GetActorLocation() + Offset + LastOffset);
                SecondEnemy->Positions.Add(Path[CellIndex + i]->GetActorLocation() - Offset - LastOffset);

            }else{

                Enemy->Positions.Add(Path[CellIndex + i]->GetActorLocation() + Offset);
                SecondEnemy->Positions.Add(Path[CellIndex + i]->GetActorLocation() - Offset);

            }

            //Every cycle I insert an obstacle.
            Transform.SetLocation(Path[CellIndex + i]->GetActorLocation() + FVector(0.f,0.f,MazeActor->ObstacleHeight));
            MazeActor->CreateObstacle(Transform);

        }

        Enemy->SetInitialValue(Cast<APawn>(Enemy)->GetActorLocation(),0,true, true);
        SecondEnemy->SetInitialValue(Cast<APawn>(SecondEnemy)->GetActorLocation(),0,true, true);

}

//Generate walls one beside the middle ad one in the angle.
void AMazeManager::GenerateSideElements(int CellIndex, int i, float HeightOffset, float SideOffset, float OffsetValue, bool Spawn,TSubclassOf<AGeneralElem> SpawnActor, TArray<AMazeCell2*> Path) {
    
    FVector Offset;
    SetOffsetVector(Path[CellIndex + 1 + i],Path[CellIndex + i],Offset,OffsetValue);

    GenerateDecorations(Path[CellIndex + i]->GetActorLocation(),
        Path[CellIndex + i]->GetActorLocation() + Offset + FVector(0.f,0.f,HeightOffset),
        Path[CellIndex + i]->GetActorLocation() + 2 * Offset ,
        Spawn,SpawnActor);
    
    bool Value = SetOffsetVector(Path[CellIndex + 1 + i],Path[CellIndex + i],Offset,OffsetValue);

    if(Value)

        GenerateDecorations(Path[CellIndex + i]->GetActorLocation(),
            (Path[CellIndex + i]->GetActorLocation() + Path[CellIndex + i + 1]->GetActorLocation())/2 - Offset + FVector(0.f,SideOffset,HeightOffset),
            (Path[CellIndex + i]->GetActorLocation() + Path[CellIndex + i + 1]->GetActorLocation())/2 - 2 * Offset + FVector(0.f,SideOffset,HeightOffset),
            Spawn,SpawnActor);

    else
        
        GenerateDecorations(Path[CellIndex + i]->GetActorLocation(),
            (Path[CellIndex + i]->GetActorLocation() + Path[CellIndex + i + 1]->GetActorLocation())/2 - Offset + FVector(SideOffset,0.f,HeightOffset) ,
            (Path[CellIndex + i]->GetActorLocation() + Path[CellIndex + i + 1]->GetActorLocation())/2 - 2 * Offset + FVector(SideOffset,0.f,HeightOffset),
            Spawn,SpawnActor);

}

void AMazeManager::TypeOfEnemies(int Index, int CellIndex, TArray<AMazeCell2*> Path) {
    
    FVector Offset;
    FVector Pos;

    switch(Index){

        case 0:

            GetWorld()->SpawnActor<AAIShooterPawn>(ShooterEnemyClass,Path[CellIndex]->GetActorLocation() , FRotator::ZeroRotator);
            GetWorld()->SpawnActor<AAIShooterPawn>(ShooterEnemyClass,Path[CellIndex + 2]->GetActorLocation() , FRotator::ZeroRotator);
            GenerateSideElements(CellIndex,0, MazeActor->ObstacleHeight, -25.f, 320.f, false, nullptr, Path);
            GenerateSideElements(CellIndex,1, MazeActor->ObstacleHeight, -25.f, 320.f, false, nullptr, Path);
            GenerateSideElements(CellIndex,2, MazeActor->ObstacleHeight, -25.f, 320.f, false, nullptr, Path);

            break;
        
        case 1:

            SetOffsetVector(Path[CellIndex + 1],Path[CellIndex],Offset,220.f);
            Pos = (Path[CellIndex]->GetActorLocation() + Path[CellIndex + 1]->GetActorLocation()) / 2;
            GetWorld()->SpawnActor<AAIBull>(BullEnemyClass, Pos + Offset/2, FRotator::ZeroRotator);
            GetWorld()->SpawnActor<AAIShooterPawn>(ShooterEnemyClass,Path[CellIndex + 2]->GetActorLocation() , FRotator::ZeroRotator);
            GenerateSideElements(CellIndex,0, MazeActor->ObstacleHeight, -25.f, 320.f, false, nullptr, Path);
            GenerateSideElements(CellIndex,1, MazeActor->ObstacleHeight, -25.f, 320.f, false,  nullptr, Path);
            GenerateSideElements(CellIndex,2, MazeActor->ObstacleHeight, -25.f, 320.f, false, nullptr, Path);

            break;

        case 2:
            
            SetOffsetVector(Path[CellIndex + 1],Path[CellIndex],Offset,100.f);
            Pos = (Path[CellIndex]->GetActorLocation() + Path[CellIndex + 1]->GetActorLocation()) / 2;
            
            GetWorld()->SpawnActor<AAIBull>(BullEnemyClass, Path[CellIndex + 1]->GetActorLocation(), GetDoorRotation(MaxPath[CellIndex + 1], MaxPath[CellIndex]));
            GetWorld()->SpawnActor<AAIBull>(BullEnemyClass, Path[CellIndex + 1]->GetActorLocation() + Offset, GetDoorRotation(MaxPath[CellIndex + 1], MaxPath[CellIndex]));
           
            GetWorld()->SpawnActor<AAIShooterPawn>(ShooterEnemyClass,Path[CellIndex + 2]->GetActorLocation() , FRotator::ZeroRotator);
            GetWorld()->SpawnActor<AAIShooterPawn>(ShooterEnemyClass,Path[CellIndex]->GetActorLocation() , FRotator::ZeroRotator);

            GetWorld()->SpawnActor<AActor>(MetalCrateClass,(Path[CellIndex]->GetActorLocation() + Path[CellIndex + 1]->GetActorLocation()) / 2 + FVector(0.f,0.f,-50.f), FRotator::ZeroRotator);
            GetWorld()->SpawnActor<AActor>(MetalCrateClass,(Path[CellIndex + 1]->GetActorLocation() + Path[CellIndex + 2]->GetActorLocation()) / 2 + FVector(0.f,0.f,-50.f), FRotator::ZeroRotator);
           
            GenerateSideElements(CellIndex,0, MazeActor->ObstacleHeight, -25.f, 320.f, false, nullptr, Path);
            GenerateSideElements(CellIndex,1, MazeActor->ObstacleHeight, -25.f, 320.f, false,  nullptr, Path);
            GenerateSideElements(CellIndex,2, MazeActor->ObstacleHeight, -25.f, 320.f, false, nullptr, Path);

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
                GenerateSideElements(CellIndex + i,0, -50.f, -40.f, 290.f, true,CrateClass, Path);

            break;
        
        case 1:
            
            SetOffsetVector(Path[CellIndex + 1],Path[CellIndex],Offset,110.f); //110
            Pos = (Path[CellIndex]->GetActorLocation() + Path[CellIndex + 1]->GetActorLocation()) / 2 + Offset;
            
            Enemy = GetWorld()->SpawnActor<AAIBull>(BullEnemyClass, Pos + Offset , FRotator::ZeroRotator);
            Enemy->bSpawnCoin = true;
            Enemy = GetWorld()->SpawnActor<AAIShooterPawn>(ShooterEnemyClass,Path[CellIndex + 2]->GetActorLocation(), FRotator::ZeroRotator);
            Enemy->bSpawnCoin = true;

            //Create Crate Actors.
            for(int i = 0; i < 3; i++)       
                GenerateSideElements(CellIndex + i,0, -50.f, -40.f, 290.f, true,CrateClass, Path);

            break;

        case 2:

            for(int i = 0; i < 3; i++){

                //Create traps in 2 cells out of 3.
                if(i != 1){

                    GetWorld()->SpawnActor<ATrap>(TrapClass, Path[CellIndex + i]->GetActorLocation() + FVector(0.f,0.f,-50.f), FRotator::ZeroRotator);
                    GetWorld()->SpawnActor<ATrap>(TrapClass, Path[CellIndex + i]->GetActorLocation() + FVector(260.f,260.f,-50.f), FRotator::ZeroRotator);
                    GetWorld()->SpawnActor<ATrap>(TrapClass, Path[CellIndex + i]->GetActorLocation() + FVector(-260.f,260.f,-50.f), FRotator::ZeroRotator);
                    GetWorld()->SpawnActor<ATrap>(TrapClass, Path[CellIndex + i]->GetActorLocation() + FVector(260.f,-260.f,-50.f), FRotator::ZeroRotator);
                    GetWorld()->SpawnActor<ATrap>(TrapClass, Path[CellIndex + i]->GetActorLocation() + FVector(-260.f,-260.f,-50.f), FRotator::ZeroRotator);

                    TArray<FVector> Positions{FVector(0.f,260.f,-50.f),FVector(0.f,-260.f,-50.f),
                        FVector(260.f,0.f,-50.f),FVector(-260.f,0.f,-50.f)};

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
                    GetWorld()->SpawnActor<AGenericDestructibleElements>(DestrElem,Path[CellIndex + i]->GetActorLocation() + FVector(260.f,260.f,-50.f),FRotator::ZeroRotator);
                    GetWorld()->SpawnActor<AGenericDestructibleElements>(DestrElem,Path[CellIndex + i]->GetActorLocation() + FVector(-260.f,260.f,-50.f),FRotator::ZeroRotator);
                    GetWorld()->SpawnActor<AGenericDestructibleElements>(DestrElem,Path[CellIndex + i]->GetActorLocation() + FVector(260.f,-260.f,-50.f),FRotator::ZeroRotator);
                    GetWorld()->SpawnActor<AGenericDestructibleElements>(DestrElem,Path[CellIndex + i]->GetActorLocation() + FVector(-260.f,-260.f,-50.f),FRotator::ZeroRotator);

                }

            }

            break;
        
        default:
            UE_LOG(LogTemp,Warning,TEXT("TypeOfCoinEnemies"));
            break;

    }

}

void AMazeManager::GenerateDoors() {

    for(int i = 2; i < MaxPath.Num() - 2; i += 10){ //MaxPath.Num() - 2

        if(i != 2 && (i - 2) % 10 == 0)
            AddDoor(FMath::RandRange(0,3),MaxPath[i]);   
        
    }
    
    PortalType(2,MaxPath[MaxPath.Num() - 2]);      

}

void AMazeManager::AddDoor(int Index, AMazeCell2* Cell) {

    int CellIndex = MaxPath.IndexOfByKey(Cell);
    ADoor* Actor;
    FTransform Transform;

    switch(Index){
        
        //KillerDoor
        case 0:
            
            GetWorld()->SpawnActor<ADoorKiller>(DoorKillerClass, (MaxPath[CellIndex]->GetActorLocation() + MaxPath[CellIndex + 1]->GetActorLocation())/2,
                    GetDoorRotation(MaxPath[CellIndex + 1], MaxPath[CellIndex]));

            break;

        case 1:

            Transform.SetLocation((MaxPath[CellIndex]->GetActorLocation() + MaxPath[CellIndex + 1]->GetActorLocation())/2);
            Transform.SetRotation(GetDoorRotation(MaxPath[CellIndex + 1], MaxPath[CellIndex]).Quaternion());
            Actor = GetWorld()->SpawnActorDeferred<ADoorRiddle>(DoorRiddleClass,Transform);
            Cast<ADoorRiddle>(Actor)->Speech = &Speech;
            Cast<ADoorRiddle>(Actor)->OldSpeech = &OldSpeech;
            Cast<ADoorRiddle>(Actor)->Questions = &Questions;
            Cast<ADoorRiddle>(Actor)->OldQuestions = &OldQuestions;
            Actor->FinishSpawning(Transform);

            break;

        case 2:

            GetWorld()->SpawnActor<ADoorAchiever>(DoorAchieverClass, (MaxPath[CellIndex]->GetActorLocation() + MaxPath[CellIndex + 1]->GetActorLocation())/2,
                    GetDoorRotation(MaxPath[CellIndex + 1], MaxPath[CellIndex]));

            break;

        case 3:
            
            GetWorld()->SpawnActor<ADoorExplorer>(DoorExplorerClass, (MaxPath[CellIndex]->GetActorLocation() + MaxPath[CellIndex + 1]->GetActorLocation())/2,
                    GetDoorRotation(MaxPath[CellIndex + 1], MaxPath[CellIndex]));

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
    
    IInterfaceMovableAI* Enemy;* Enemy;
    int CellIndex = Path.IndexOfByKey(Cell);
    float OffsetX;
    float OffsetY;
    
    Cell->DestroyFloor();
    CreatePlatforms(Cell,150.f);
            
    Path[CellIndex + 2]->DestroyFloor();
    CreatePlatforms(Path[CellIndex + 2],150.f);
    
    GetWorld()->SpawnActor<ACoinController>(CoinClass,Path[CellIndex]->GetActorLocation() - FVector(0.f,0.f,10.f),Path[CellIndex]->GetActorRotation());          
    GetWorld()->SpawnActor<ACoinController>(CoinClass,Path[CellIndex + 2]->GetActorLocation() - FVector(0.f,0.f,10.f),Path[CellIndex + 2]->GetActorRotation());          

    switch(Index){

        case 0:

            GetWorld()->SpawnActor<AGeneralElem>(CrateClass,Path[CellIndex + 1]->GetActorLocation() - FVector(0.f,0.f,50.f),Path[CellIndex + 1]->GetActorRotation());
            OffsetX = FMath::RandRange(100.f,200.f);
            OffsetY = FMath::RandRange(100.f,200.f);
            GetWorld()->SpawnActor<AAIShooterPawn>(ShooterEnemyClass,Path[CellIndex + 1]->GetActorLocation() + FVector(OffsetX,OffsetY,10.f),Path[CellIndex + 1]->GetActorRotation())->bSpawnCoin = true;

            break;
        
        case 1:

            OffsetX = FMath::RandRange(100.f,200.f);
            OffsetY = FMath::RandRange(100.f,200.f);
            GetWorld()->SpawnActor<AAIShooterPawn>(ShooterEnemyClass,Path[CellIndex + 1]->GetActorLocation() + FVector(-OffsetX,-OffsetY,10.f),Path[CellIndex + 1]->GetActorRotation());
            GetWorld()->SpawnActor<AAIShooterPawn>(ShooterEnemyClass,Path[CellIndex + 1]->GetActorLocation() + FVector(OffsetX,OffsetY,10.f),Path[CellIndex + 1]->GetActorRotation());

            break;

        case 2:

            OffsetX = FMath::RandRange(100.f,200.f);
            OffsetY = FMath::RandRange(100.f,200.f);
            GetWorld()->SpawnActor<IInterfaceMovableAI>(MoveAIClass2,Path[CellIndex + 1]->GetActorLocation() + FVector(OffsetX,OffsetY,10.f), FRotator::ZeroRotator)->SetInitialValue(Path[CellIndex + 1]->GetActorLocation(),1,true, true);
            GetWorld()->SpawnActor<IInterfaceMovableAI>(MoveAIClass2,Path[CellIndex + 1]->GetActorLocation() + FVector(-OffsetX,-OffsetY,10.f), FRotator::ZeroRotator)->SetInitialValue(Path[CellIndex + 1]->GetActorLocation(),1,true, true);

            break;

        case 3:

            if(FMath::RandRange(0,1) == 0){
                Enemy = GetWorld()->SpawnActor<IInterfaceMovableAI>(PatrolEnemyClass,Path[CellIndex + 1]->GetActorLocation()  + FVector(250.f,250.f,-10.f), FRotator::ZeroRotator);
                Enemy->Positions.Add(Path[CellIndex + 1]->GetActorLocation() + FVector(300.f,300.f,-10.f));
                Enemy->Positions.Add(Path[CellIndex + 1]->GetActorLocation() + FVector(-300.f,-300.f,-10.f));
                Enemy->SetInitialValue(Cast<APawn>(Enemy)->GetActorLocation(),0,true, true);
            }else{
                Enemy = GetWorld()->SpawnActor<IInterfaceMovableAI>(PatrolEnemyClass,Path[CellIndex + 1]->GetActorLocation() +  FVector(250.f,-250.f,-10.f), FRotator::ZeroRotator);
                Enemy->Positions.Add(Path[CellIndex + 1]->GetActorLocation() + FVector(300.f,-300.f,-10.f));
                Enemy->Positions.Add(Path[CellIndex + 1]->GetActorLocation() + FVector(-300.f,300.f,-10.f));
                Enemy->SetInitialValue(Cast<APawn>(Enemy)->GetActorLocation(),0,true, true);
            }

            break;

    }

}

void AMazeManager::CreatePlatforms(AMazeCell2* Cell, float Value) {
    
    GetWorld()->SpawnActor<AShakingFallenPlatform>(ShakingFallenPlatform,Cell->GetActorLocation() + FVector(0.f,0.f,-60.f),Cell->GetActorRotation());
    /*GetWorld()->SpawnActor<AShakingFallenPlatform>(ShakingFallenPlatform,Cell->GetActorLocation() + FVector(Value,Value,-60.f),Cell->GetActorRotation());
    GetWorld()->SpawnActor<AShakingFallenPlatform>(ShakingFallenPlatform,Cell->GetActorLocation() + FVector(-Value,Value,-60.f),Cell->GetActorRotation());
    GetWorld()->SpawnActor<AShakingFallenPlatform>(ShakingFallenPlatform,Cell->GetActorLocation() + FVector(-Value,-Value,-60.f),Cell->GetActorRotation());
    */
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

        //Create Maze for explorer.
        case 0 :

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
            ArenaSpawnLocation.RemoveAt(NumExtr);

            //Create the door
            Door = GetWorld()->SpawnActor<ADoor>(DoorClass,  (MaxPath[CellIndex]->GetActorLocation() + MaxPath[CellIndex + 1]->GetActorLocation())/2,
                GetDoorRotation(MaxPath[CellIndex + 1], MaxPath[CellIndex]));
            Door->SetActorScale3D(FVector(1.75f,1.f,0.75f));
 
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

        case 1:

            //Create the door
            Door = GetWorld()->SpawnActor<ADoor>(DoorClass,  (MaxPath[CellIndex]->GetActorLocation() + MaxPath[CellIndex + 1]->GetActorLocation())/2,
                GetDoorRotation(MaxPath[CellIndex + 1], MaxPath[CellIndex]));
            Door->SetActorScale3D(FVector(1.75f,1.f,0.75f));

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

            RoomKiller->StartPortalPos = StartPortal->GetActorLocation();

            break;

        case 2:

            //Create the door
            Door = GetWorld()->SpawnActor<ADoor>(DoorClass,  (MaxPath[CellIndex]->GetActorLocation() + MaxPath[CellIndex + 1]->GetActorLocation())/2,
                GetDoorRotation(MaxPath[CellIndex + 1], MaxPath[CellIndex]));
            Door->SetActorScale3D(FVector(1.75f,1.f,0.75f));

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

            RoomSocializer->StartPortalPos = StartPortal->GetActorLocation();

            break;

        case 3:
            
            Door = GetWorld()->SpawnActor<ADoor>(DoorClass,  (MaxPath[CellIndex]->GetActorLocation() + MaxPath[CellIndex + 1]->GetActorLocation())/2,
                GetDoorRotation(MaxPath[CellIndex + 1], MaxPath[CellIndex]));
            Door->SetActorScale3D(FVector(1.75f,1.f,0.75f));

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

            //RoomKiller->StartPortalPos = StartPortal->GetActorLocation();

            break;
    }
    
}

void AMazeManager::PopulateOtherPath() {
    
    /*for(Graph<TArray<AMazeCell2*>> Path : OtherPaths){

        AMazeCell2* CentralCell = (*Path.GetCurrentNode())[0];   
        AMazeCell2* FirstCell = (*Path.GetCurrentNode())[1];

        GetWorld()->SpawnActor<ADestructibleElements>(DestructibleShakeClass, (CentralCell->GetActorLocation() + FirstCell->GetActorLocation())/2,
            GetDoorRotation(FirstCell,CentralCell));

        TArray<TArray<AMazeCell2 *> *> Leaves = Path.GetLeaves();

        for(TArray<AMazeCell2 *>* Leaf: Leaves){
            
            SpawnExtraElem(FMath::RandRange(0,2),(*Leaf)[Leaf->Num() - 1],(*Leaf)[Leaf->Num() - 2]);

        }

        TArray<AMazeCell2*> T;

        for(TArray< AMazeCell2* >* Nodes : Path.GetNodes()){
            
            for(AMazeCell2* Nod : (*Nodes)){

                if(!T.Contains(Nod))
                    T.Add(Nod);

            }

        }

        UE_LOG(LogTemp,Warning,TEXT("%i"), T.Num() - 1);


    }*/

}

void AMazeManager::SpawnExtraElem(int Index, AMazeCell2* AfterCell, AMazeCell2* BeforeCell) {

    switch(Index){

        case 0:
            
            GetWorld()->SpawnActor<AStatueInteractElem>(StatueClass, AfterCell->GetActorLocation(),
                GetDoorRotation(AfterCell,BeforeCell));

            break;

        case 1:
            
            GetWorld()->SpawnActor<AHeart>(HeartClass, AfterCell->GetActorLocation(),
                GetDoorRotation(AfterCell,BeforeCell));

            break;

        case 2:

            GetWorld()->SpawnActor<APawnInteractiveClass>(SpokenNpcClass, AfterCell->GetActorLocation(),
                GetDoorRotation(AfterCell,BeforeCell));

            break;

        case 3:

            if(HatClasses.Num() > 0 && FMath::RandRange(0,9) > 2){

                int NumExtr = FMath::RandRange(0,HatClasses.Num() - 1);
                GetWorld()->SpawnActor<AHat>(HatClasses[NumExtr], AfterCell->GetActorLocation(), FRotator::ZeroRotator);
                HatClasses.RemoveAt(NumExtr);

            }else{

                GetWorld()->SpawnActor<ACoinController>(CoinClass, AfterCell->GetActorLocation(),
                GetDoorRotation(AfterCell,BeforeCell));

            }

            break;

    }
    
}

#pragma endregion
