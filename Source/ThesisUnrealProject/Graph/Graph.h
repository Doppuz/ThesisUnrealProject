// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Side.h"
#include "Node.h"
#include "CoreMinimal.h"

//template<class F,class S>
class THESISUNREALPROJECT_API Graph{

public:
	//Graph();
	//~Graph();

	void AddNode(Space*);

	void AddSide(Space*, Space*, float);

	TArray<Space*> GetNodes();
	TArray<Side*> GetSides(Space* N);

	void DeleteNode(Space*);

	TArray<Space*> GetLeaves(float RoomLimit);
	TArray<Space*> GetLeavesNoSpace();
	TArray<Space*> GetNodesMaxDistance();

protected:

	TMap<Space*, TArray<Side*>> Map;

private:
	int GetDepth(Space*);
};
