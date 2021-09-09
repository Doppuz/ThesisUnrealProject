// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeManager.h"
#include "Containers/Array.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "MazeCell2.h"
#include "RoomMaze.h"
#include "MazeGenerationCreation2.h"
#include "Kismet/GameplayStatics.h"
#include "MazePopulate.h"
#include "../Elements/Maze/Maze.h"
#include "../Elements/GeneralElements/Door.h"
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

// Sets default values
AMazeManager::AMazeManager()
{
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
        
        AddDoors(0);

        GenerateEnemies();

        /*PrintMaze(MaxPath, FColor(0.f,0.f,100.f));

        for(int i = 0; i < OtherPaths.Num(); i++){
            for(TArray<AMazeCell2*>* Cell : OtherPaths[i].GetNodes())
                PrintMaze((*Cell),FColor(0.f,100.f,0.f));

        }
        UE_LOG(LogTemp,Warning,TEXT("Others path: %i"), OtherPaths.Num());*/

    }


    //MapIncrement = 100.0/(MazeGraph->GetGraphSize() - 3.0 * MazeActorRoom);
    
    //Populate = new MazeGenerationPopulate(MazeGraph,ChestClass, CoinClass, CrateElementsClass, GetWorld());

    /*PopulateActor = GetWorld()->SpawnActor<AMazePopulate>(PopulateClass,FVector::ZeroVector,FRotator::ZeroRotator);

    if(PopulateActor != nullptr){
    
        PopulateActor->MazeGraph = MazeGraph;
        //PopulateActor->Rooms = Generator->Rooms;

        //Check for cells with 3 walls.
        PopulateActor->DepthVisit(MazeGraph->GetCurrentNode());
        //PopulateActor->AddDoors();
        
        //MazeGraph->SetVisitedToZero();
        //Populate->DynamicDepthVisit((*Maze)[0][0],5);
        //Populate->PopulateChest();

        //MazeGraph->SetVisitedToZero();
    
    }*/
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
			DrawDebugLine(GetWorld(),
			FVector(Edge->From->GetActorLocation().X, Edge->From->GetActorLocation().Y, Edge->From->GetActorLocation().Z + 1100), //700
			FVector(Edge->To->GetActorLocation().X,Edge->To->GetActorLocation().Y,Edge->To->GetActorLocation().Z + 1100),
			Color,
			true,
			50.f,
			0,
			50.f);
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
    DepthVisitWrapper(Start,0, TArray<AMazeCell2*>(),MazeCellMax);
    MaxPath = MazeCellMax;
    TArray<AMazeCell2*> NewPath;
    Graph<TArray<AMazeCell2*>> OtherGraph;
    CreateOtherPaths(&NewPath,MaxPath[0],nullptr,0,&OtherGraph,nullptr);
    int a = 0;
    //PrintMaze(MaxPath, FColor(0.f,0.f,0.f));

}

void AMazeManager::DepthVisitWrapper(AMazeCell2* Current, float Cost, TArray<AMazeCell2*> CurrentVisitedCell,
        TArray<AMazeCell2*> & MazeCellMax) {
    
    TArray<Side<AMazeCell2>*> Sides = MazeGraph->GetSides(Current); 
    Current->bIsVisited = true;
    CurrentVisitedCell.Add(Current);

    for(Side<AMazeCell2>* S: MazeGraph->GetSides(Current)){
        if(S->To->bIsVisited != true)
            DepthVisitWrapper(S->To, Cost + 1, CurrentVisitedCell, MazeCellMax);
    }
    
    //Last Cell of the current path. 
    //AMazeCell* LastCell = CurrentVisitedCell[CurrentVisitedCell.Num() - 1];

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
void AMazeManager::CreateOtherPaths(TArray<AMazeCell2*>* NewPath, AMazeCell2* Current, AMazeCell2* Previous, int MaxPathIndex, Graph<TArray<AMazeCell2*>>* OtherGraph,
    TArray<AMazeCell2*>* CurrentNode){
    
    TArray<Side<AMazeCell2>*> Sides = MazeGraph->GetSides(Current);
    
    //The process is divided in 3 parts. First check if I am in a crossroad.
    if(!MaxPath.Contains(Current) && Sides.Num() > 2){
        
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


    }

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

                AddRoom(FMath::RandRange(0,3),Door,RoomDoor,RoomCenter[Sides->To->RoomNumber],Sides->To); //FMath::RandRange(0,3)

                /*PosRot= MaxPath[Index]->GetWallPosition(WallNumberRoom);
				ADoor* RoomDoor = GetWorld()->SpawnActor<ADoor>(DoorClass,PosRot.Position + FVector(0.f,0.f,Door->Distance),FRotator(0.f,90.f,0.f) + PosRot.Rotation);
                RoomDoor->SetActorScale3D(FVector(1.7f,1.f,0.75f));
                RoomDoor->SetDoorDirection(true);

                //Spawn the trigger
                ATrigger* Trigger = GetWorld()->SpawnActor<ATrigger>(TriggerClass,PosRot.Position ,PosRot.Rotation); 
		        Trigger->ChangeVisibility(true);
                Trigger->SetActorScale3D(FVector(1.f,1.5f,2.f));*/

                //Spawn of the room
                /*FVector Pos = (*Rooms)[Sides->To->NumberRoom].Room[4]->GetActorLocation();
                FRotator Rot = FRotator::ZeroRotator;
                //ARumbleArenaDoorNpc* Arena = GetWorld()->SpawnActor<ARumbleArenaDoorNpc>(RumbleArenaClass,Pos,Rot);
                AArenaEnemies* Arena = GetWorld()->SpawnActor<AArenaEnemies>(EnemiesArenaClass,Pos,Rot);
                Arena->Door = Door;
                //Arena->RoomDoor = RoomDoor;*/

                /*const FTransform SpawnLocAndRotation;
                AMazeArena* Arena = GetWorld()->SpawnActor<AMazeArena>(MazeArenaClass, SpawnLocAndRotation);
                Arena->Door = Door;*/

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

void AMazeManager::GenerateEnemies() {
    
    for(int i = 2; i < MaxPath.Num() - 2; i += 4){ //MaxPath.Num() - 2

        /*if(FMath::RandRange(0,1) == 0)
            GetWorld()->SpawnActor<AAIBull>(BullEnemyClass,MaxPath[i]->GetActorLocation(), FRotator::ZeroRotator);
        else
            GetWorld()->SpawnActor<AAIShooterPawn>(ShooterEnemyClass,MaxPath[i]->GetActorLocation(), FRotator::ZeroRotator);*/
        
        AddEnemy(FMath::RandRange(0,3), MaxPath[i - 1]);
        
    }

}

void AMazeManager::AddEnemy(int Index, AMazeCell2* Cell) {

    IInterfaceMovableAI* Enemy;
    int CellIndex;
        FVector Offset;

    switch (Index){

    case 0:
        GetWorld()->SpawnActor<AAIBull>(BullEnemyClass,Cell->GetActorLocation(), FRotator::ZeroRotator);
        break;
    
    case 1:
        GetWorld()->SpawnActor<AAIShooterPawn>(ShooterEnemyClass,Cell->GetActorLocation(), FRotator::ZeroRotator);
        break;
    
    case 2:
        
        CellIndex = MaxPath.IndexOfByKey(Cell);

        SetOffsetVector(CellIndex,Offset);

        Enemy = GetWorld()->SpawnActor<IInterfaceMovableAI>(PatrolEnemyClass,Cell->GetActorLocation() + Offset, FRotator::ZeroRotator);
        Enemy->Positions.Add(Cell->GetActorLocation() + Offset);
        
        SetOffsetVector(CellIndex + 1,Offset);
        Enemy->Positions.Add(MaxPath[CellIndex + 1]->GetActorLocation() + Offset);

        SetOffsetVector(CellIndex + 2,Offset);
        Enemy->Positions.Add(MaxPath[CellIndex + 2]->GetActorLocation() + Offset);
        
        Enemy->SetInitialValue(Cell->GetActorLocation(),1,true);
 
        SetOffsetVector(CellIndex,Offset);

        Enemy = GetWorld()->SpawnActor<IInterfaceMovableAI>(PatrolEnemyClass,Cell->GetActorLocation() - Offset, FRotator::ZeroRotator);
        Enemy->Positions.Add(Cell->GetActorLocation() - Offset);

        SetOffsetVector(CellIndex + 1,Offset);
        Enemy->Positions.Add(MaxPath[CellIndex + 1]->GetActorLocation() - Offset);
        
        SetOffsetVector(CellIndex + 2,Offset);
        Enemy->Positions.Add(MaxPath[CellIndex + 2]->GetActorLocation() - Offset);

        Enemy->SetInitialValue(Cell->GetActorLocation(),1,true);

        //TypeOfPatrolswalls(CellIndex);

        break;

    case 3:

        Enemy = GetWorld()->SpawnActor<IInterfaceMovableAI>(MoveAIClass,Cell->GetActorLocation(), FRotator::ZeroRotator);
        Enemy->Positions.Add(Cell->GetActorLocation());
        Enemy->Positions.Add(MaxPath[MaxPath.IndexOfByKey(Cell) + 1]->GetActorLocation());
        Enemy->Positions.Add(MaxPath[MaxPath.IndexOfByKey(Cell) + 2]->GetActorLocation());
        Enemy->SetInitialValue(Cell->GetActorLocation(),1,true);

        break;
    
    }

}


#pragma region Obstacle

void AMazeManager::SetOffsetVector(int Index, FVector& Offset) {
        
        if((MaxPath[Index]->GetActorLocation().X - MaxPath[Index + 1]->GetActorLocation().X) < 0.1f)
            Offset = FVector(250.f,0.f,0.f);
        else
            Offset = FVector(0.f,250.f,0.f);

}

void AMazeManager::LineTracing(FHitResult& Hit,FVector StartPosition, FVector EndPosition) {

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	GetWorld()->LineTraceSingleByChannel(Hit,StartPosition,EndPosition,ECollisionChannel::ECC_GameTraceChannel10,CollisionParams);
    
}

void AMazeManager::GeneratePatrolsWalls(FVector StartPos, FVector EndPos, FVector EndLineTracingPos) {
    
    FTransform Transform;
    Transform.SetRotation(FRotator::ZeroRotator.Quaternion());
    
    FHitResult Hit;

    LineTracing(Hit,StartPos,EndLineTracingPos);
    if(Hit.GetActor() !=nullptr){
        Transform.SetLocation(EndPos);
        MazeActor->CreateObstacle(Transform);
    }

}

void AMazeManager::TypeOfPatrolswalls(int CellIndex) {
    
    for(int i = 0; i< 3; i++){

        if((MaxPath[CellIndex + i]->GetActorLocation().X - MaxPath[CellIndex + i + 1]->GetActorLocation().X) < 0.1f){

            GeneratePatrolsWalls(MaxPath[CellIndex + i]->GetActorLocation(),
                MaxPath[CellIndex + i]->GetActorLocation() + FVector(Distance/2 - MazeActor->ObstacleSize,0.f,MazeActor->ObstacleHeight),
                MaxPath[CellIndex + i]->GetActorLocation() + FVector(Distance - MazeActor->ObstacleSize,0.f,MazeActor->ObstacleHeight));

            GeneratePatrolsWalls(MaxPath[CellIndex + i]->GetActorLocation(),
                (MaxPath[CellIndex + i]->GetActorLocation() + MaxPath[CellIndex + i + 1]->GetActorLocation())/2 - FVector(Distance/2 - MazeActor->ObstacleSize,0.f,-MazeActor->ObstacleHeight),
                (MaxPath[CellIndex + i]->GetActorLocation() + MaxPath[CellIndex + i + 1]->GetActorLocation())/2 - FVector(Distance - MazeActor->ObstacleSize,0.f,-MazeActor->ObstacleHeight));

        }else{

            GeneratePatrolsWalls(MaxPath[CellIndex + i]->GetActorLocation(),
                MaxPath[CellIndex + i]->GetActorLocation() + FVector(0.f,Distance/2 - MazeActor->ObstacleSize,MazeActor->ObstacleHeight),
                MaxPath[CellIndex + i]->GetActorLocation() + FVector(0.f,Distance  - MazeActor->ObstacleSize,MazeActor->ObstacleHeight));
                
            GeneratePatrolsWalls(MaxPath[CellIndex + i]->GetActorLocation(),
                (MaxPath[CellIndex + i]->GetActorLocation() + MaxPath[CellIndex + i + 1]->GetActorLocation())/2 - FVector(0.f,Distance/2 - MazeActor->ObstacleSize,-MazeActor->ObstacleHeight),
                (MaxPath[CellIndex + i]->GetActorLocation() + MaxPath[CellIndex + i + 1]->GetActorLocation())/2 - FVector(0.f,Distance - MazeActor->ObstacleSize,-MazeActor->ObstacleHeight));


        }

    }

}


#pragma endregion

#pragma endregion
