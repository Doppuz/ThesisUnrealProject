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
#include "../Elements/Room/MazeArena/MazeArena.h"
#include "../Elements/Triggers/Trigger.h"
#include "../Elements/Triggers/TriggerSpawnNight.h"
#include "../Elements/Stairs/Stair.h"

// Sets default values
AMazeManager::AMazeManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    this->Distance = 770.f;
}

AMazeManager::~AMazeManager() {
    delete MazeGraph;
}

#pragma region MazeManager

// Called when the game starts or when spawned
void AMazeManager::BeginPlay()
{
	Super::BeginPlay();

	//Initialize all the components for the maze creation.
    MazeGraph = new Graph<AMazeCell2>();
    MazeActor = GetWorld()->SpawnActor<AMaze>(MazeActorClass,FVector(0,0,Depth),FRotator::ZeroRotator);
    
    StandardMazeCreation();

    DepthVisit(MazeGraph->GetCurrentNode());

    if(PopulateMaze){
        AddDoors(0);
    }

    int a = 4;

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
void AMazeManager::PrintMaze(TArray<AMazeCell2*> Nodes) {

    for (AMazeCell2* Cell : Nodes) {
		for(Side<AMazeCell2>* Edge: MazeGraph->GetSides(Cell)){
			DrawDebugLine(GetWorld(),
			FVector(Edge->From->GetActorLocation().X, Edge->From->GetActorLocation().Y, Edge->From->GetActorLocation().Z + 1100), //700
			FVector(Edge->To->GetActorLocation().X,Edge->To->GetActorLocation().Y,Edge->To->GetActorLocation().Z + 1100),
			FColor(100, 0, 0),
			true,
			50.f,
			0,
			50.f);
		}
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
            FRotator Rotator;

            AMazeCell2* CellActor = GetWorld()->SpawnActor<AMazeCell2>(CellClass,FVector(i * (-Distance), j * Distance, Depth),Rotator);
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

void AMazeManager::DepthVisit(AMazeCell2* Start) {
    
    MazeGraph->SetVisitedToZero();
    TArray<AMazeCell2*> MazeCellMax;
    DepthVisitWrapper(Start,0, TArray<AMazeCell2*>(),MazeCellMax);
    MaxPath = MazeCellMax;
    //PrintMaze(MaxPath);

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
                Pos.Z = 600.f;
                ADoor* RoomDoor = GetWorld()->SpawnActor<ADoor>(DoorClass,Pos,Rot);
                RoomDoor->SetActorScale3D(FVector(1.7f,3.f,0.75f));
                RoomDoor->SetDoorDirection(true);

                AddRoom(2,Door,RoomDoor,RoomCenter[Sides->To->RoomNumber],Sides->To);
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
    AStair* Stair;
    FVector MazeLocation;
    FVector DoorPos;
    
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

            Arena = GetWorld()->SpawnActor<AMazeArena>(MazeArenaClass, FVector::ZeroVector, FRotator::ZeroRotator);
            Arena->Door = Door;
            Location = RoomDoor->GetActorLocation();
            Location.Z = -100.f;

            //If condition to rotate the stair and the room according to the door.
            if(RoomDoor->GetActorLocation().X == RoomCell->GetActorLocation().X){
            
                //Check if the everything haa to be positionate on the right or left side.
                if(RoomCell->GetActorLocation().Y > RoomDoor->GetActorLocation().Y){
                    
                    Stair = GetWorld()->SpawnActor<AStair>(StairClass, Location,RoomDoor->GetActorRotation() + FRotator(0.f,90.f,0.f)); 
                    MazeLocation = FVector(RoomDoor->GetActorLocation().X,RoomDoor->GetActorLocation().Y + Stair->StepsDistance * Stair->StepsNumber + Stair->InitialOffset,
                        Stair->StepsHeightDistance * (Stair->StepsNumber - 1));
                    Cast<AMazeArena>(Arena)->SetMazeLocation(MazeLocation);
                    //Here SetMazeRotation is useless because it would be Fotator(0.f,0.f,0.f).
                    DoorPos = MazeLocation - FVector(0.f,Stair->InitialOffset,0.f);

                }else{
                    
                    Stair = GetWorld()->SpawnActor<AStair>(StairClass, Location,RoomDoor->GetActorRotation() - FRotator(0.f,90.f,0.f));  
                    MazeLocation = FVector(RoomDoor->GetActorLocation().X,RoomDoor->GetActorLocation().Y - Stair->StepsDistance * Stair->StepsNumber - Stair->InitialOffset,
                        Stair->StepsHeightDistance * (Stair->StepsNumber - 1));
                    Cast<AMazeArena>(Arena)->SetMazeLocation(MazeLocation);
                    Cast<AMazeArena>(Arena)->SetMazeRotation(FRotator(0.f,180.f,0.f));
                    DoorPos = MazeLocation + FVector(0.f,-Stair->InitialOffset,0.f);

                }
                    
            }else{


                if(RoomCell->GetActorLocation().X > RoomDoor->GetActorLocation().X){
                                    
                    Stair = GetWorld()->SpawnActor<AStair>(StairClass, Location,RoomDoor->GetActorRotation() - FRotator(0.f,90.f,0.f));  
                    MazeLocation = FVector(RoomDoor->GetActorLocation().X + Stair->StepsDistance * Stair->StepsNumber + Stair->InitialOffset,RoomDoor->GetActorLocation().Y,
                        Stair->StepsHeightDistance * (Stair->StepsNumber - 1));
                    Cast<AMazeArena>(Arena)->SetMazeLocation(MazeLocation);
                    Cast<AMazeArena>(Arena)->SetMazeRotation(FRotator(0.f,-90.f,0.f));
                    
                    DoorPos = MazeLocation - FVector(Stair->InitialOffset,0.f,0.f);;
              
                }else{

                    Stair = GetWorld()->SpawnActor<AStair>(StairClass, Location,RoomDoor->GetActorRotation() + FRotator(0.f,90.f,0.f)); 
                    MazeLocation = FVector(RoomDoor->GetActorLocation().X - Stair->StepsDistance * Stair->StepsNumber - Stair->InitialOffset,RoomDoor->GetActorLocation().Y,
                        Stair->StepsHeightDistance * (Stair->StepsNumber - 1));
                    Cast<AMazeArena>(Arena)->SetMazeLocation(MazeLocation);
                    Cast<AMazeArena>(Arena)->SetMazeRotation(FRotator(0.f,90.f,0.f)); 
                    DoorPos = MazeLocation + FVector(Stair->InitialOffset,0.f,0.f);;

                }
            }

            //Create the door of the underground maze.
            DoorPos.Z += 400.f;
            RoomDoor->SetActorLocation(DoorPos);
            RoomDoor->SetDoorDirection(true);
            RoomDoor->Speed = 3.0f;
            Cast<AMazeArena>(Arena)->RoomDoor = RoomDoor;
            RoomDoor->SetActorScale3D(FVector(1.7f,3.f,0.75f));

            //Spawn night trigger
            FTransform SpawnLocAndRotation;
            
            Graph<AMazeCell2>* ArenaGraph = Cast<AMazeArena>(Arena)->MazeManager->MazeGraph;

            for(Side<AMazeCell2>* S: ArenaGraph->GetSides(ArenaGraph->GetNodes()[0])){
                
                SpawnLocAndRotation.SetRotation(RoomDoor->GetActorRotation().Quaternion());
                SpawnLocAndRotation.SetLocation(S->To->GetActorLocation());
                Cast<AMazeArena>(Arena)->CreateNightTrigger(SpawnLocAndRotation);

            }


            break;

    }

}

#pragma endregion
