// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Graph/Graph.h"
#include "MazePopulate.generated.h"

class AMazeCell2;
class AMazeCell;

class AChestController;
class ACoinController;
class AGeneralElem;
class ADoor;
class RoomMaze;
class AGeneralRoomWithDoor;
class ATrigger;
class AMazeManager;

UCLASS()
class THESISUNREALPROJECT_API AMazePopulate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMazePopulate();

	virtual void DepthVisit(AMazeCell* Start);
	void DynamicDepthVisit(AMazeCell* Current);
	void PopulateChest();
	virtual void AddDoors();

	//Cell's graph.
	Graph<AMazeCell2>* MazeGraph = nullptr;

	//Room array
	TArray<RoomMaze>* Rooms;

	//Contains the path that leads to the exit.
	TArray<AMazeCell*> MaxPath;

protected:

	//I sort all the cell with 3 walls.
	TMap<AMazeCell*,int> Wall3Cells;

	//Class for chest spawn.
	UPROPERTY(EditAnywhere, Category = "Elements")
	TSubclassOf<AChestController> ChestClass;

	//Class for coins spawn.
	UPROPERTY(EditAnywhere, Category = "Elements")
	TSubclassOf<ACoinController> CoinClass;

	//Class for Elements spawn.
	UPROPERTY(EditAnywhere, Category = "Elements")
	TSubclassOf<AGeneralElem> CrateElementsClass;

	UPROPERTY(EditAnywhere, Category = "Elements")
	TSubclassOf<ADoor> DoorClass;

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

	//Contains the last path of the Dynamic visit.
	TArray<AMazeCell*> OldPath;

	//Used to substitute the NewPath to the OldPath during the Dynamic visit.
	TArray<AMazeCell*> NewPath;

	//Methods
	void DepthVisitWrapper(AMazeCell* Current, float Cost, TArray<AMazeCell*> CurrentVisitedCell,
		TArray<AMazeCell*> & MazeCellList);

	void DynamicDepthVisitWrapper(AMazeCell* Current, int DepthLimit);

	void SetDynamicVisitedToZero();

	void AddDoorsWrapper(int);


};
