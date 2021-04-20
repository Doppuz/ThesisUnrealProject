// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <vector>
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Graph/Graph.h"
#include "MazeGeneratorManager.generated.h"

class AMazeCell;
class RoomMaze;
class MazeGenerationCreation;
class MazeGenerationPopulate;
class AChestController;
class ACoinController;

UCLASS()
class THESISUNREALPROJECT_API AMazeGeneratorManager : public AActor{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMazeGeneratorManager();
	~AMazeGeneratorManager();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	static int NumberOfChest; 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	
//---------- Parameter for Maze generation ------------------
	UPROPERTY(EditAnywhere, Category = "MazeGeneration")
	int Length = 10;

	UPROPERTY(EditAnywhere, Category = "MazeGeneration")
	int Height = 10;

	UPROPERTY(EditAnywhere, Category = "MazeGeneration")
	int MazeObstacle = 10;

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
	//Graph of the maze
	Graph* MazeGraph;

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
};
