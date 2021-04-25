// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class Graph;
class AMazeCell;
class AChestController;
class ACoinController;

/**
 * 
 */
class THESISUNREALPROJECT_API MazeGenerationPopulate
{
public:
	MazeGenerationPopulate(Graph*, TSubclassOf<AChestController>, TSubclassOf<ACoinController>, UWorld*);
	~MazeGenerationPopulate();

	void DepthVisit(AMazeCell* Start);
	void PopulateChest();

private:
	//Cell's graph.
	Graph* MazeGraph = nullptr;

	//I sort all the cell with 3 walls.
	TMap<AMazeCell*,int> Wall3Cells;

	//Class for chest spawn.
	TSubclassOf<AChestController> ChestClass;

	//Class for chest spawn.
	TSubclassOf<ACoinController> CoinClass;

	UWorld* World;

	//Class for chest spawn.
	//TSubclassOf<

	//Methods
	void DepthVisitWrapper(AMazeCell* Current, float Cost, TArray<AMazeCell*> CurrentVisitedCell,
		TArray<AMazeCell*> & MazeCellList);
};
