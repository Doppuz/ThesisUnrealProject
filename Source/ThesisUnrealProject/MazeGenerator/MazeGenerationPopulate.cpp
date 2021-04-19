// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeGenerationPopulate.h"
#include "MazeCell.h"
#include "../Graph/Graph.h"
#include "../Elements/ChestController.h"
#include "MazeGeneratorManager.h"

MazeGenerationPopulate::MazeGenerationPopulate(Graph* MazeGraph, TSubclassOf<AChestController> ChestClass, UWorld* World){
    this->MazeGraph = MazeGraph;
    this->ChestClass = ChestClass;
    this->World = World;
}

MazeGenerationPopulate::~MazeGenerationPopulate(){

}

void MazeGenerationPopulate::DepthVisit(AMazeCell* Start) {
    SetVisitedToZero();
    DepthVisitWrapper(Start,0);
    int a = 0;
}

void MazeGenerationPopulate::DepthVisitWrapper(AMazeCell* Current, float Cost) {
    TArray<Side*> Sides = MazeGraph->GetSides(Current); 
    Current->bIsVisited = true;

    //UE_LOG(LogTemp, Warning, TEXT("%d %d"), Current->I, Current->J);
    if(Current->WallNumbers == 3 && !(Current->I == 0 && Current->J == 0))
        Wall3Cells.Add(Current,Cost);
    for(Side* S: MazeGraph->GetSides(Current)){
        if(S->To->bIsVisited != true)
            DepthVisitWrapper(S->To, Cost + 1);
    }
}

void MazeGenerationPopulate::SetVisitedToZero() {
    for(AMazeCell* Cell: MazeGraph->GetNodes())
        Cell->bIsVisited = false;
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
    
    if(Cells.Num() < AMazeGeneratorManager::NumberOfChest)
        UE_LOG(LogTemp,Warning,TEXT("Not enough cells to put chests in."));

    //First I take the one with the bigger distance and than I divided it to make it always closer to me.
    for(int I = 0; I < AMazeGeneratorManager::NumberOfChest && Cells.Num() > I; I++){
        Position = FVector(Cells[(int) Cells.Num() / (I+1) - 1]->GetActorLocation().X,
            Cells[(int) Cells.Num() / (I+1) - 1]->GetActorLocation().Y,
            Cells[(int) Cells.Num() / (I+1) - 1]->GetActorLocation().Z + 500);
        Rotation = FRotator(0,-90 + 90 * (Cells[(int) Cells.Num() / (I+1) - 1]->LastHiddenWall - 1),0);
        World->SpawnActor<AChestController>(ChestClass,Position,Rotation);
    }

}
