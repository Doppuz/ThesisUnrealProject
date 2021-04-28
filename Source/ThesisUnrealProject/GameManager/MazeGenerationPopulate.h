// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class Graph;
class AMazeCell;
class AChestController;
class ACoinController;
class AGeneralElem;

/**
 * 
 */
class THESISUNREALPROJECT_API MazeGenerationPopulate
{
public:
	MazeGenerationPopulate(Graph*, TSubclassOf<AChestController>, TSubclassOf<ACoinController>,
		TSubclassOf<AGeneralElem>, UWorld*);
	~MazeGenerationPopulate();

	void DepthVisit(AMazeCell* Start);
	void DynamicDepthVisit(AMazeCell* Current);
	void PopulateChest();

private:
	//Cell's graph.
	Graph* MazeGraph = nullptr;

	//I sort all the cell with 3 walls.
	TMap<AMazeCell*,int> Wall3Cells;

	//Class for chest spawn.
	TSubclassOf<AChestController> ChestClass;

	//Class for coins spawn.
	TSubclassOf<ACoinController> CoinClass;

	UWorld* World;

	//Class for Elements spawn.
	TSubclassOf<AGeneralElem> CrateElementsClass;

	//Contains the path the leads to the exit.
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
};
