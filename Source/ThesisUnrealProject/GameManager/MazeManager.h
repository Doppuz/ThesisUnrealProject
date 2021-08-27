// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "../Graph/Graph.h"
#include "GameFramework/Actor.h"
#include "MazeManager.generated.h"

class AMazeCell2;
class RoomMaze;
class MazeGenerationCreation2;
class AdaptingExperienceManager;
class AMazePopulate;
class AMaze;
class ADoor;
class AGeneralRoomWithDoor;
class ATrigger;

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

private:

#pragma region MazeManager

//---------- Parameter for Maze generation ------------------
	UPROPERTY(EditAnywhere, Category = "MazeGeneration")
	int Length = 10;

	UPROPERTY(EditAnywhere, Category = "MazeGeneration")
	int Height = 10;

	UPROPERTY(EditAnywhere, Category = "MazeGeneration")
	int MazeObstacle = 0;

	UPROPERTY(EditAnywhere, Category = "MazeGeneration")
	int MazeRooms = 4;

	UPROPERTY(EditAnywhere, Category = "MazeGeneration")
	float Depth = 0;

	UPROPERTY(EditAnywhere, Category = "MazeGeneration")
	TSubclassOf<AMazeCell2> CellClass;

	//Graph of the maze
	Graph<AMazeCell2>* MazeGraph;

	//Maze meshes actor .
	UPROPERTY(EditAnywhere, Category = "MazeGeneration")
	AMaze* Maze2;

	//Pointer to the AdaptingExperienceManager class
	AdaptingExperienceManager* Adapting;

	FVector PlayerPosition;

	//World percentage increment
    float MapIncrement;

#pragma endregion

#pragma region MazeCreation

public:
	
	void StandardMazeCreation();

	void PrintMaze(TArray<AMazeCell2*> Nodes);

	//Keep track of the center the rooms.
	TMap<int,FVector> RoomCenter;
	
	//Used to keep track of the rooms with a door.
	TArray<int> RoomWithDoor;

private:

	//Methods
	void InitializeMaze();
	void CreateObstacle(int ObstaclesNumber);
	void CreateRooms(int);
	bool CheckRoomIntersection(TArray<AMazeCell2*>,int);
	void CreateMaze(AMazeCell2*,AMazeCell2*);

	//Distance between 2 cells.
	float Distance;

#pragma endregion

#pragma region Populate

public:

	//Class for trigger spawn
	UPROPERTY(EditAnywhere, Category = "Elements")
	TSubclassOf<ATrigger> TriggerClass;

	//Rooms
	UPROPERTY(EditAnywhere, Category = "Elements")
	TSubclassOf<AGeneralRoomWithDoor> RumbleArenaClass;
	
	UPROPERTY(EditAnywhere, Category = "Elements")
	TSubclassOf<AGeneralRoomWithDoor> EnemiesArenaClass;
	
	UPROPERTY(EditAnywhere, Category = "Elements")
	TSubclassOf<AGeneralRoomWithDoor> MazeArenaClass;

private:

	//Contains the path that leads to the exit.
	TArray<AMazeCell2*> MaxPath;

	UPROPERTY(EditAnywhere, Category = "Populate")
	TSubclassOf<ADoor> DoorClass;

	virtual void DepthVisit(AMazeCell2* Start);
	void DepthVisitWrapper(AMazeCell2* Current, float Cost, TArray<AMazeCell2*> CurrentVisitedCell,
		TArray<AMazeCell2*> & MazeCellList);
	void SetDynamicVisitedToZero();

	void AddDoors(int);

	//Choose a room within a range to insert it in the level.
	void AddRoom(int, ADoor*, ADoor*, FVector);


#pragma endregion
};
