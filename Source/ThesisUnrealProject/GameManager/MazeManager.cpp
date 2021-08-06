// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeManager.h"
#include "Containers/Array.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "MazeCell.h"
#include "RoomMaze.h"
#include "MazeGenerationCreation.h"
#include "Kismet/GameplayStatics.h"
#include "MazePopulate.h"

// Sets default values
AMazeManager::AMazeManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

AMazeManager::~AMazeManager() {
	delete Maze;
    delete Rooms;
    delete MazeGraph;
    delete Generator;
}

// Called when the game starts or when spawned
void AMazeManager::BeginPlay()
{
	Super::BeginPlay();

	//Initialize all the components for the maze creation.
    Maze = new TArray<TArray<AMazeCell*>>();
    Rooms = new TArray<RoomMaze>();
    MazeGraph = new Graph();
    
    Generator = new MazeGenerationCreation(Length,Height,MazeObstacle,Maze2Room,CellClass,
        Maze,Rooms,MazeGraph,GetWorld());

    Generator->StandardMazeCreation();

    //MapIncrement = 100.0/(MazeGraph->GetGraphSize() - 3.0 * Maze2Room);
    
    //Populate = new MazeGenerationPopulate(MazeGraph,ChestClass, CoinClass, CrateElementsClass, GetWorld());

    PopulateActor->MazeGraph = MazeGraph;
    PopulateActor->Rooms = Generator->Rooms;

    //Check for cells with 3 walls.
    PopulateActor->DepthVisit((*Maze)[0][0]);
    PopulateActor->AddDoors();
    
    //MazeGraph->SetVisitedToZero();
    //Populate->DynamicDepthVisit((*Maze)[0][0],5);
    //Populate->PopulateChest();

    MazeGraph->SetVisitedToZero();
}

// Called every frame
void AMazeManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

