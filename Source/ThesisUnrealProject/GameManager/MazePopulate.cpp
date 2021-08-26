// Fill out your copyright notice in the Description page of Project Settings.


#include "MazePopulate.h"
#include "MazeCell.h"
#include "MazeCell2.h"
#include "../Graph/Graph.h"
#include "../Elements/GeneralElements/ChestController.h"
#include "../Elements/GeneralElements/CoinController.h"
#include "../CustomGameMode.h"
#include "../Elements/GeneralElements/Door.h"
#include "RoomMaze.h"
#include "MazeCell.h"
#include "../Elements/Room/RumbleArena/RumbleArenaDoorNpc.h"
#include "../Elements/Room/ArenaEnemies/ArenaEnemies.h"
#include "../Elements/Room/MazeArena/MazeArena.h"
#include "Kismet/GameplayStatics.h"
#include "MazeManager.h"
#include "../Elements/Triggers/Trigger.h"
#include  "DrawDebugHelpers.h"

// Sets default values
AMazePopulate::AMazePopulate(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

//DepthVisit to search 3 walls-cells and to search the longest path.
void AMazePopulate::DepthVisit(AMazeCell2* Start) {
    MazeGraph->SetVisitedToZero();
    TArray<AMazeCell2*> MazeCellMax;
    DepthVisitWrapper(Start,0, TArray<AMazeCell2*>(),MazeCellMax);
    MaxPath = MazeCellMax;
    PrintMaze();
    /*MazeCellMax[MazeCellMax.Num() - 1]->HideWall(1);
    MazeCellMax[MazeCellMax.Num() - 1]->HideWall(2);
    MazeCellMax[MazeCellMax.Num() - 1]->HideWall(3);
    MazeCellMax[MazeCellMax.Num() - 1]->HideWall(4);
    MazeCellMax[MazeCellMax.Num() - 1]->HideWall(0);*/
    
}

void AMazePopulate::DepthVisitWrapper(AMazeCell2* Current, float Cost, TArray<AMazeCell2*> CurrentVisitedCell,
        TArray<AMazeCell2*> & MazeCellMax) {
    TArray<Side<AMazeCell2>*> Sides = MazeGraph->GetSides(Current); 
    Current->bIsVisited = true;
    CurrentVisitedCell.Add(Current);

    for(Side<AMazeCell2>* S: MazeGraph->GetSides(Current)){
        if(S->To->bIsVisited != true)
            DepthVisitWrapper(S->To, Cost + 1, CurrentVisitedCell, MazeCellMax);
    }

    /*if(Current->WallNumbers == 3 && !(Current->I == 0 && Current->J == 0))
        Wall3Cells.Add(Current,Cost);*/
    //else if (Current->NumberRoom == -1)
    //    Current->PopulateElem(CrateElementsClass);
    
    //Last Cell of the current path. 
    //AMazeCell* LastCell = CurrentVisitedCell[CurrentVisitedCell.Num() - 1];

    //Search for the maximum path (uncomment below to put the exit in one of the sides)
    if(CurrentVisitedCell.Num() > MazeCellMax.Num()) //&& (LastCell->I == 0 || LastCell->I == 12 ||
                                                    //    LastCell->J == 0 || LastCell->J == 12))
        MazeCellMax = CurrentVisitedCell;

}

//Dynamic visit that is computed every time I reach a new cell.
void AMazePopulate::DynamicDepthVisit(AMazeCell2* Current) {
   /* NewPath.Empty();
    SetDynamicVisitedToZero();
    DynamicDepthVisitWrapper(Current,9);
    for(AMazeCell* Cell: OldPath){
        Cell->RemoveAllElem();
    }
    OldPath = NewPath;*/
}

//Wrapper to the visit. New path has the new Nodes. OldPath has the nodes that are not present in the new path anymore.
void AMazePopulate::DynamicDepthVisitWrapper(AMazeCell* Current, int DepthLimit) {
    
    /*Current->bDynamicIsVisited = true;

    TArray<Side*> Sides = MazeGraph->GetSides(Current);
    
    for(Side* S: MazeGraph->GetSides(Current)){
        if(S->To->bDynamicIsVisited != true && DepthLimit != 0)
            DynamicDepthVisitWrapper(S->To, DepthLimit - 1);
    }

    if (Current->NumberRoom == -1 && !OldPath.Contains(Current))
        Current->PopulateElem(CrateElementsClass);

    OldPath.Remove(Current);
    NewPath.Add(Current);*/

}

//Set at 0 the value of bDynamicVisited variable in AMazeCell to 0.
void AMazePopulate::SetDynamicVisitedToZero() {
	/*for(AMazeCell* Cell: OldPath)
    	Cell->bDynamicIsVisited = false;*/
}

//Index = current cell
void AMazePopulate::AddDoorsWrapper(int Index){

	/*for(Side* Sides: MazeGraph->GetSides(MaxPath[Index])){
		
		if(Sides->To->NumberRoom != -1){
			
			if(Index + 1 < MaxPath.Num()){

                FPositionRotation PosRot;

                //Wall number to block the street
				int WallNumber = MaxPath[Index]->GiveFrontWall(MaxPath[Index + 1]);

                //Wall number to close the room
				int WallNumberRoom = MaxPath[Index]->GiveFrontWall(Sides->To);

                //Spawn the doors
				PosRot= MaxPath[Index]->GetWallPosition(WallNumber);
				ADoor* Door = GetWorld()->SpawnActor<ADoor>(DoorClass,PosRot.Position,FRotator(0.f,90.f,0.f) + PosRot.Rotation);
                Door->SetActorScale3D(FVector(1.7f,1.f,0.75f));

                PosRot= MaxPath[Index]->GetWallPosition(WallNumberRoom);
				ADoor* RoomDoor = GetWorld()->SpawnActor<ADoor>(DoorClass,PosRot.Position + FVector(0.f,0.f,Door->Distance),FRotator(0.f,90.f,0.f) + PosRot.Rotation);
                RoomDoor->SetActorScale3D(FVector(1.7f,1.f,0.75f));
                RoomDoor->SetDoorDirection(true);

                //Spawn the trigger
                ATrigger* Trigger = GetWorld()->SpawnActor<ATrigger>(TriggerClass,PosRot.Position ,PosRot.Rotation); 
		        Trigger->ChangeVisibility(true);
                Trigger->SetActorScale3D(FVector(1.f,1.5f,2.f));

                //Spawn of the room
                /*FVector Pos = (*Rooms)[Sides->To->NumberRoom].Room[4]->GetActorLocation();
                FRotator Rot = FRotator::ZeroRotator;
                //ARumbleArenaDoorNpc* Arena = GetWorld()->SpawnActor<ARumbleArenaDoorNpc>(RumbleArenaClass,Pos,Rot);
                AArenaEnemies* Arena = GetWorld()->SpawnActor<AArenaEnemies>(EnemiesArenaClass,Pos,Rot);
                Arena->Door = Door;
                //Arena->RoomDoor = RoomDoor;*/

                /*const FTransform SpawnLocAndRotation;
                AMazeArena* Arena = GetWorld()->SpawnActor<AMazeArena>(MazeArenaClass, SpawnLocAndRotation);
                Arena->Door = Door;

			}

		}

	}

    if(Index + 1 < MaxPath.Num()){
        AddDoorsWrapper(++Index);
    }
    //if(Sides.Num() != 0)
    //    AddDoorsWrapper(Sides[0]->To);*/

}

//Used to add Doors to block the main path.
void AMazePopulate::AddDoors() {
    
   // AddDoorsWrapper(0);
    
}

void AMazePopulate::PrintMaze() {
    
    TArray<AMazeCell2*> Nodes = MaxPath;

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


//Spawn the chests in the position where there are 3 walls.
void AMazePopulate::PopulateChest() {
    /*TArray<AMazeCell*> Cells;
    FVector Position;
    FRotator Rotation;
    
    Wall3Cells.ValueSort([](int A, int B){
        return A < B;
    });

    Wall3Cells.GetKeys(Cells);

    int ChestNumber = Cast<ACustomGameMode>(GetWorld()->GetAuthGameMode())->NumberOfChest;
    
    if(Cells.Num() < ChestNumber)
        UE_LOG(LogTemp,Warning,TEXT("Not enough cells to put chests in."));

    //First I take the one with the bigger distance and than I divided it to make it always closer to me.
    for(int I = 0; I < ChestNumber && Cells.Num() > I; I++){
        Position = FVector(Cells[(int) Cells.Num() / (I+1) - 1]->GetActorLocation().X,
            Cells[(int) Cells.Num() / (I+1) - 1]->GetActorLocation().Y,
            Cells[(int) Cells.Num() / (I+1) - 1]->GetActorLocation().Z + 500);
        Rotation = FRotator(0,-90 + 90 * (Cells[(int) Cells.Num() / (I+1) - 1]->LastHiddenWall - 1),0);
        AActor* Chest = GetWorld()->SpawnActor<AChestController>(ChestClass,Position,Rotation);
        //Chest->SetFolderPath(TEXT("Chests"));
        Cells[(int) Cells.Num() / (I+1) - 1]->AddElem(Chest);
        Cells.RemoveAt((int) Cells.Num() / (I+1) - 1);
    }

    //The rest of the 3 walls-cells are popolated with coins.
    for(int I = 0; I < Cells.Num(); I++){
        Position = FVector(Cells[I]->GetActorLocation().X,
            Cells[I]->GetActorLocation().Y,
            Cells[I]->GetActorLocation().Z + 200);
        Rotation = FRotator(0,0,0);
        AActor* Coin = GetWorld()->SpawnActor<ACoinController>(CoinClass,Position,Rotation);
        Cells[(int) Cells.Num() / (I+1) - 1]->AddElem(Coin);
        //Coin->SetFolderPath(TEXT("Coins"));
    }

    MaxPath[MaxPath.Num() - 1]->RemoveAllElem();*/

}

