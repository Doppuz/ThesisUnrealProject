// Fill out your copyright notice in the Description page of Project Settings.


#include "MazePopulateUnderground.h"
#include "../Elements/Puzzle/PuzzleButton.h"
#include "MazeCell.h"
#include "../Graph/Graph.h"


void AMazePopulateUnderground::DepthVisit(AMazeCell2* Start) {
    
    //MazeGraph->SetVisitedToZero();
    TArray<AMazeCell2*> MazeCellMax;
    DepthVisitWrapper(Start,0, TArray<AMazeCell2*>(),MazeCellMax);
    MaxPath = MazeCellMax;

}

void AMazePopulateUnderground::AddDoors() {
    
}
