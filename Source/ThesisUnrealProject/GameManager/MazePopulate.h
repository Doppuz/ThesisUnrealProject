// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MazePopulate.generated.h"

class Graph;
class AMazeCell;
class AChestController;
class ACoinController;
class AGeneralElem;
class ADoor;

UCLASS()
class THESISUNREALPROJECT_API AMazePopulate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMazePopulate();

	void DepthVisit(AMazeCell* Start);
	void DynamicDepthVisit(AMazeCell* Current);
	void PopulateChest();
	void AddDoors();

	//Cell's graph.
	Graph* MazeGraph = nullptr;

private:

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

	//Contains the path that leads to the exit.
	TArray<AMazeCell*> MaxPath;

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
