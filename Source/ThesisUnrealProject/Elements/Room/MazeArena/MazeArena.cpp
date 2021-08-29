// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeArena.h"
#include "Components/BoxComponent.h"
#include "../../../GameManager/MazeCell2.h"
#include "../../../GameManager/MazeManager.h"
#include "../../../GameManager/MazePopulate.h"
#include "../../Puzzle/PuzzleButton.h"
#include "../../Maze/Maze.h"

AMazeArena::AMazeArena() {
    
    Collider->SetCollisionProfileName("NoCollision");

}


void AMazeArena::BeginPlay() {

    Super::BeginPlay();

    const FTransform SpawnLocAndRotation;
    MazeManager = GetWorld()->SpawnActorDeferred<AMazeManager>(MazeManagerClass, SpawnLocAndRotation);
    MazeManager->Depth = -750.f;
    MazeManager->Length = 5;
    MazeManager->Height = 5;
    MazeManager->MazeRooms = 0;
    MazeManager->PopulateMaze = false;
    MazeManager->FinishSpawning(SpawnLocAndRotation);

    TArray<AMazeCell2*> MazeCellMax = MazeManager->MaxPath;// = MazeManager->PopulateActor->MaxPath;

    FVector Pos = MazeCellMax[MazeCellMax.Num() - 1]->GetActorLocation() + FVector(0.f,0.f,35.f);
    FRotator Rot = MazeCellMax[MazeCellMax.Num() - 1]->GetActorRotation();

    APuzzleButton* Button = GetWorld()->SpawnActor<APuzzleButton>(PuzzleButtonClass, Pos, Rot);
    Button->Overlap.AddDynamic(this,&AMazeArena::OpenDoor);
    
}


void AMazeArena::SetMazeLocation(FVector Pos) {
    
    MazeManager->MazeActor->SetActorLocation(Pos);

}