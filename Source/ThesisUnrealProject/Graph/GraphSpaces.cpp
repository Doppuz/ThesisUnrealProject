// Fill out your copyright notice in the Description page of Project Settings.


#include "GraphSpaces.h"
#include "Space.h"

GraphSpaces::GraphSpaces()
{
}

GraphSpaces::~GraphSpaces(){
}

TArray<Node*> GraphSpaces::GetLeaves(float RoomLimit) {
	TArray<Node*> Leaves = GetNodes();
	TArray<Node*> Result;

	for (int i = 0; i < Leaves.Num(); i++) {
		Space* TmpSpace = (Space *)Leaves[i];
	}

	if(Leaves.Num() > 1)
		Leaves.RemoveAt(0);

	for (Node* N: Leaves) {
		Space* TmpSpace = (Space *) N;

		if (Map[TmpSpace].Num() < 2 && TmpSpace->Size > RoomLimit)
			Result.Add(N);
		
	}
	return Result;
}