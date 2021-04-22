// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "Graph/Graph.h"
#include "CustomGameMode.generated.h"

class AMazeCell;
class RoomMaze;
class MazeGenerationCreation;
class MazeGenerationPopulate;
class AChestController;
class ACoinController;

UCLASS()
class THESISUNREALPROJECT_API ACustomGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	
	ACustomGameMode();
    ~ACustomGameMode();
	
	int GetCoins() const;
	void IncreaseCoins();

    float GetPercentage() const;
	void IncreasePercentage();

	/** Remove the current menu widget and create a new one from the specified class, if provided. */
    UFUNCTION(BlueprintCallable, Category = "UMG Game")
    void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

	UUserWidget* GetCurrentWidgetUI();

    //NumberOfChest
    int NumberOfChest; 

    //NumberOfChest
    int NumberOfCoins; 

    //Graph of the maze
	Graph* MazeGraph;

protected:

    /** Called when the game starts. */
    virtual void BeginPlay() override;

    /** The widget class we will use as our menu when the game starts. */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
    TSubclassOf<UUserWidget> StartingWidgetClass;

    /** The widget instance that we are using as our menu. */
    UPROPERTY()
    UUserWidget* CurrentWidget;

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

	//Pointer to the MazeGenerationPopolate class
	MazeGenerationPopulate* Populate;

	FVector PlayerPosition;
//---------------------------------------------------
	UPROPERTY(EditAnywhere, Category = "Elements")
	TSubclassOf<AChestController> ChestClass;

	UPROPERTY(EditAnywhere, Category = "Elements")
	TSubclassOf<ACoinController> CoinClass;

//World percentage increment
    float MapIncrement;

};
