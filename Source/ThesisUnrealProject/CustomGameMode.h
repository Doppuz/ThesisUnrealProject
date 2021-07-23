// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "Graph/Graph.h"
#include "GameModeAbstract.h"
#include "CustomGameMode.generated.h"

class AMazeCell;
class RoomMaze;
class MazeGenerationCreation;
class MazeGenerationPopulate;
class AChestController;
class ACoinController;
class AGeneralElem;
class AdaptingExperienceManager;

UCLASS()
class THESISUNREALPROJECT_API ACustomGameMode : public AGameModeAbstract
{
	GENERATED_BODY()
	
public:
	
	ACustomGameMode();
    ~ACustomGameMode();
	
	int GetCoins() const;
	void IncreaseCoins();

    float GetPercentage() const;
	void IncreasePercentage();

    float GetAchieverValue() const;
    float GetKillerValue() const;
    float GetExplorerValue() const;
    float GetSocializerValue() const;

    //NumberOfChest
    int NumberOfChest; 

    //NumberOfChest
    int NumberOfCoins; 

    //Graph of the maze
	Graph* MazeGraph;

	//Pointer to the MazeGenerationPopolate class
	MazeGenerationPopulate* Populate;

protected:

    /** Called when the game starts. */
    virtual void BeginPlay() override;

private:
	
//---------- Parameter for Maze generation ------------------
	UPROPERTY(EditAnywhere, Category = "MazeGeneration")
	int Length = 10;

	UPROPERTY(EditAnywhere, Category = "MazeGeneration")
	int Height = 10;

	UPROPERTY(EditAnywhere, Category = "MazeGeneration")
	int MazeObstacle = 0;

	UPROPERTY(EditAnywhere, Category = "MazeGeneration")
	int Maze2Room = 4;
	UPROPERTY(EditAnywhere, Category = "MazeGeneration")
	int Maze3Room = 0;
	UPROPERTY(EditAnywhere, Category = "MazeGeneration")
	int Maze4Room = 0;

	UPROPERTY(EditAnywhere, Category = "MazeGeneration")
	TSubclassOf<AMazeCell> CellClass;

	//Contains all the cells for the creation.
	TArray<TArray<AMazeCell*>> *Maze = nullptr;
	
	//Contains all the rooms
	TArray<RoomMaze> *Rooms = nullptr;

	//Pointer to the MazeGenerationCreation class
	MazeGenerationCreation* Generator;

	//Pointer to the AdaptingExperienceManager class
	AdaptingExperienceManager* Adapting;

	FVector PlayerPosition;
//---------------------------------------------------
	UPROPERTY(EditAnywhere, Category = "Elements")
	TSubclassOf<AChestController> ChestClass;

	UPROPERTY(EditAnywhere, Category = "Elements")
	TSubclassOf<ACoinController> CoinClass;

	UPROPERTY(EditAnywhere, Category = "Elements")
	TSubclassOf<AGeneralElem> CrateElementsClass;

//World percentage increment
    float MapIncrement;

};
