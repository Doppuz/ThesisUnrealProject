// Copyright Epic Games, Inc. All Rights Reserved.


#include "CustomGameMode.h"
#include "CustomGameState.h"
#include "Graph/Graph.h"
#include "Containers/Array.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "GameManager/MazeCell.h"
#include "GameManager/RoomMaze.h"
#include "GameManager/MazeGenerationCreation.h"
#include "Kismet/GameplayStatics.h"
#include "GameManager/MazeGenerationPopulate.h"
#include "Elements/ChestController.h"
#include "Elements/CoinController.h"
#include "Elements/CrateElements.h"
#include "UI/UIWidgetDialog.h"
#include "UI/UIBox.h"


ACustomGameMode::ACustomGameMode() {
    GameStateClass = ACustomGameState::StaticClass();
    NumberOfChest = 2;
}


ACustomGameMode::~ACustomGameMode() {
    delete Maze;
    delete Rooms;
    delete MazeGraph;
    delete Generator;
    delete Populate;
}

void ACustomGameMode::BeginPlay() {
    Super::BeginPlay();

	UUIWidgetDialog* DialogWidget = Cast<UUIWidgetDialog>(CurrentWidget);
    DialogWidget->HideSizeBox();
    DialogWidget->TextBox->BoxContainer->Visibility = ESlateVisibility::Hidden;

    //Initialize all the components for the maze creation.
    Maze = new TArray<TArray<AMazeCell*>>();
    Rooms = new TArray<RoomMaze>();
    MazeGraph = new Graph();
    
    Generator = new MazeGenerationCreation(Length,Height,MazeObstacle,Maze2Room,CellClass,
        Maze,Rooms,MazeGraph,GetWorld());

    Generator->StandardMazeCreation();

    MapIncrement = 100.0/(MazeGraph->GetGraphSize() - 3.0 * Maze2Room);
    
    Populate = new MazeGenerationPopulate(MazeGraph,ChestClass, CoinClass, CrateElementsClass, GetWorld());

    float p = 0;

    //Check for cells with 3 walls.
    Populate->DepthVisit((*Maze)[0][0]);
    Populate->AddDoors();
    
    //MazeGraph->SetVisitedToZero();
    //Populate->DynamicDepthVisit((*Maze)[0][0],5);
    //Populate->PopulateChest();

    MazeGraph->SetVisitedToZero();
}


//--- Get and Set for the coins and world percentage.

int ACustomGameMode::GetCoins() const{
    return GetGameState<ACustomGameState>()->CoinNumber;
}

void ACustomGameMode::IncreaseCoins() {
    GetGameState<ACustomGameState>()->CoinNumber += 1;
}

float ACustomGameMode::GetPercentage() const{
    return GetGameState<ACustomGameState>()->MapPercentage;
}

void ACustomGameMode::IncreasePercentage() {
    GetGameState<ACustomGameState>()->MapPercentage += MapIncrement;
}
