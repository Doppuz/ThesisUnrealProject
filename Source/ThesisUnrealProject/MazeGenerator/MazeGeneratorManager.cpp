// Fill out your copyright notice in the Description page of Project Settings.

#include "MazeGeneratorManager.h"

#include "../Graph/Graph.h"
#include "Containers/Array.h"
#include "CoupleStruct.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "MazeCell.h"
#include "RoomMaze.h"
#include "MazeGenerationCreation.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMazeGeneratorManager::AMazeGeneratorManager() {
    // Set this actor to call Tick() every frame.  You can turn this off to
    // improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

AMazeGeneratorManager::~AMazeGeneratorManager() {
    delete Maze;
    delete Rooms;
    delete MazeGraph;
    delete Generator;
}

// Called when the game starts or when spawned
void AMazeGeneratorManager::BeginPlay() {
    Super::BeginPlay();

    Maze = new TArray<TArray<AMazeCell*>>();
    Rooms = new TArray<RoomMaze>();
    MazeGraph = new Graph();
    
    Generator = new MazeGenerationCreation(Length,Height,MazeObstacle,Maze2Room,CellClass,
        Maze,Rooms,MazeGraph,GetWorld());

    Generator->StandardMazeCreation();
    
    /*PlayerPosition = (*Maze)[0][0]->GetActorLocation();

    TArray<AActor *> OutActors;
    UGameplayStatics::GetAllActorsWithTag(GetWorld(),TEXT("PlayerPos"),OutActors);

    if(OutActors.Num() > 0)
        OutActors[0]->SetActorLocation(PlayerPosition);
    else
		UE_LOG(LogTemp, Warning, TEXT("No PlayerPos found"));*/
}

// Called every frame
void AMazeGeneratorManager::Tick(float DeltaTime) { Super::Tick(DeltaTime); }
