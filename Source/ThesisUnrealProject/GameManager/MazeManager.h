// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "../Graph/Graph.h"
#include "GameFramework/Actor.h"
#include "MazeManager.generated.h"

class AMazeCell;
class RoomMaze;
class MazeGenerationCreation;
class AdaptingExperienceManager;

UCLASS()
class THESISUNREALPROJECT_API AMazeManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMazeManager();

	~AMazeManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	   //Graph of the maze
	Graph* MazeGraph;

	//Pointer to the MazeGenerationPopolate class
	UPROPERTY(EditAnywhere)
	class AMazePopulate* PopulateActor;

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

	//World percentage increment
    float MapIncrement;

};
