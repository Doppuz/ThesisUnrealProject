// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeGenerationPopulate.h"
#include "MazeCell.h"
#include "../Graph/Graph.h"
#include "../Elements/ChestController.h"
#include "../Elements/CoinController.h"
#include "../CustomGameMode.h"

MazeGenerationPopulate::MazeGenerationPopulate(Graph* MazeGraph, TSubclassOf<AChestController> ChestClass, TSubclassOf<ACoinController> CoinClass,
                                            TSubclassOf<AGeneralElem> CrateElementsClass, UWorld* World){
    this->MazeGraph = MazeGraph;
    this->ChestClass = ChestClass;
    this->World = World;
    this->CoinClass = CoinClass;
    this->CrateElementsClass = CrateElementsClass;
}

MazeGenerationPopulate::~MazeGenerationPopulate(){

}

//DepthVisit to search 3 walls-cells and to search the longest path.
void MazeGenerationPopulate::DepthVisit(AMazeCell* Start) {
    MazeGraph->SetVisitedToZero();
    TArray<AMazeCell*> MazeCellMax;
    DepthVisitWrapper(Start,0, TArray<AMazeCell*>(),MazeCellMax);
    MaxPath = MazeCellMax;
    MazeCellMax[MazeCellMax.Num() - 1]->HideWall(1);
    MazeCellMax[MazeCellMax.Num() - 1]->HideWall(2);
    MazeCellMax[MazeCellMax.Num() - 1]->HideWall(3);
    MazeCellMax[MazeCellMax.Num() - 1]->HideWall(4);
    
}

void MazeGenerationPopulate::DepthVisitWrapper(AMazeCell* Current, float Cost, TArray<AMazeCell*> CurrentVisitedCell,
        TArray<AMazeCell*> & MazeCellMax) {
    TArray<Side*> Sides = MazeGraph->GetSides(Current); 
    Current->bIsVisited = true;
    CurrentVisitedCell.Add(Current);

    for(Side* S: MazeGraph->GetSides(Current)){
        if(S->To->bIsVisited != true)
            DepthVisitWrapper(S->To, Cost + 1, CurrentVisitedCell, MazeCellMax);
    }

    if(Current->WallNumbers == 3 && !(Current->I == 0 && Current->J == 0))
        Wall3Cells.Add(Current,Cost);
    else if (Current->NumberRoom == -1)
        Current->PopulateElem(CrateElementsClass);
    
    //Last Cell of the current path. 
    AMazeCell* LastCell = CurrentVisitedCell[CurrentVisitedCell.Num() - 1];

    //Search for the maximum path
    if(CurrentVisitedCell.Num() > MazeCellMax.Num() && (LastCell->I == 0 || LastCell->I == 9 ||
                                                        LastCell->J == 0 || LastCell->J == 9))
        MazeCellMax = CurrentVisitedCell;

}

//Dynamic visit that is computed every time I reach a new cell.
void MazeGenerationPopulate::DynamicDepthVisit(AMazeCell* Current) {
    NewPath.Empty();
    SetDynamicVisitedToZero();
    DynamicDepthVisitWrapper(Current,9);
    for(AMazeCell* Cell: OldPath){
        Cell->RemoveAllElem();
    }
    OldPath = NewPath;
}

//Wrapper to the visit. New path has the new Nodes. OldPath has the nodes that are not present in the new path anymore.
void MazeGenerationPopulate::DynamicDepthVisitWrapper(AMazeCell* Current, int DepthLimit) {
    
    Current->bDynamicIsVisited = true;

    TArray<Side*> Sides = MazeGraph->GetSides(Current);
    
    for(Side* S: MazeGraph->GetSides(Current)){
        if(S->To->bDynamicIsVisited != true && DepthLimit != 0)
            DynamicDepthVisitWrapper(S->To, DepthLimit - 1);
    }

    if (Current->NumberRoom == -1 && !OldPath.Contains(Current))
        Current->PopulateElem(CrateElementsClass);

    OldPath.Remove(Current);
    NewPath.Add(Current);

}

//Set at 0 the value of bDynamicVisited variable in AMazeCell to 0.
void MazeGenerationPopulate::SetDynamicVisitedToZero() {
	for(AMazeCell* Cell: OldPath)
    	Cell->bDynamicIsVisited = false;
}


//Spawn the chests in the position where there are 3 walls.
void MazeGenerationPopulate::PopulateChest() {
    TArray<AMazeCell*> Cells;
    FVector Position;
    FRotator Rotation;
    
    Wall3Cells.ValueSort([](int A, int B){
        return A < B;
    });

    Wall3Cells.GetKeys(Cells);

    int ChestNumber = Cast<ACustomGameMode>(World->GetAuthGameMode())->NumberOfChest;
    
    if(Cells.Num() < ChestNumber)
        UE_LOG(LogTemp,Warning,TEXT("Not enough cells to put chests in."));

    //First I take the one with the bigger distance and than I divided it to make it always closer to me.
    for(int I = 0; I < ChestNumber && Cells.Num() > I; I++){
        Position = FVector(Cells[(int) Cells.Num() / (I+1) - 1]->GetActorLocation().X,
            Cells[(int) Cells.Num() / (I+1) - 1]->GetActorLocation().Y,
            Cells[(int) Cells.Num() / (I+1) - 1]->GetActorLocation().Z + 500);
        Rotation = FRotator(0,-90 + 90 * (Cells[(int) Cells.Num() / (I+1) - 1]->LastHiddenWall - 1),0);
        AActor* Chest = World->SpawnActor<AChestController>(ChestClass,Position,Rotation);
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
        AActor* Coin = World->SpawnActor<ACoinController>(CoinClass,Position,Rotation);
        Cells[(int) Cells.Num() / (I+1) - 1]->AddElem(Coin);
        //Coin->SetFolderPath(TEXT("Coins"));
    }

    MaxPath[MaxPath.Num() - 1]->RemoveAllElem();

}

