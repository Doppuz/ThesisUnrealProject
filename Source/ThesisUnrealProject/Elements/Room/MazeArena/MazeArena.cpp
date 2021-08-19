// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeArena.h"
#include "Components/BoxComponent.h"
#include "../../../GameManager/MazeCell.h"
#include "../../../GameManager/MazeManager.h"
#include "../../../GameManager/MazePopulate.h"
#include "../../Puzzle/PuzzleButton.h"

AMazeArena::AMazeArena() {
    
    Collider->SetCollisionProfileName("NoCollision");

}

void AMazeArena::BeginPlay() {

    Super::BeginPlay();

    const FTransform SpawnLocAndRotation;
    AMazeManager* MazeManager = GetWorld()->SpawnActor<AMazeManager>(MazeManagerClass, SpawnLocAndRotation);

    TArray<AMazeCell*> MazeCellMax = MazeManager->PopulateActor->MaxPath;

    FVector Pos = MazeCellMax[MazeCellMax.Num() - 1]->GetActorLocation() + FVector(0.f,0.f,35.f);
    FRotator Rot = MazeCellMax[MazeCellMax.Num() - 1]->GetActorRotation();

    APuzzleButton* Button = GetWorld()->SpawnActor<APuzzleButton>(PuzzleButtonClass, Pos, Rot);
    Button->Overlap.AddDynamic(this,&AMazeArena::OpenDoor);
    
}
