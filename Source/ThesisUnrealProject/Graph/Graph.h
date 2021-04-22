// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../MazeGenerator/MazeCell.h"
#include "Side.h"
#include "Node.h"
#include "CoreMinimal.h"

//template<class F,class S>
class THESISUNREALPROJECT_API Graph{

public:

	void AddNode(AMazeCell*);

	void AddSide(AMazeCell*, AMazeCell*, float);

	TArray<AMazeCell*> GetNodes();
	TArray<Side*> GetSides(AMazeCell* N);

	void DeleteNode(AMazeCell*);

	TArray<AMazeCell*> GetLeaves(float RoomLimit);
	TArray<AMazeCell*> GetLeavesNoSpace();
	TArray<AMazeCell*> GetNodesMaxDistance();

	AMazeCell* GetCurrentNode();

	void SetVisitedToZero();

	//Move the current node to the next cell.
	void MoveCurrentNode(AMazeCell* );

	int GetGraphSize();

protected:

	TMap<AMazeCell*, TArray<Side*>> Map;

private:
	int GetDepth(AMazeCell*);

	//Used to store the current node the player is in right now.
	AMazeCell* CurrentNode = nullptr;
};
