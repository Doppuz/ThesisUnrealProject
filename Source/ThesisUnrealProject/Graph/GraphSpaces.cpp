// Fill out your copyright notice in the Description page of Project Settings.


#include "GraphSpaces.h"
#include "Space.h"

/*
TArray<Space*> GraphSpaces::GetLeaves(float RoomLimit) {
	TArray<Space*> Leaves = GetNodes();
	TArray<Space*> Result;

	if(Leaves.Num() > 1)
		Leaves.RemoveAt(0);

	for (Space* TmpSpace: Leaves) {

		if (Map[TmpSpace].Num() < 2 && TmpSpace->Size > RoomLimit)
			Result.Add(TmpSpace);
		
	}
	return Result;
}

TArray<Space*> GraphSpaces::GetLeavesNoSpace() {
	TArray<Space*> Leaves = GetNodes();
	TArray<Space*> Result;

	if(Leaves.Num() > 1)
		Leaves.RemoveAt(0);

	for (Space* TmpSpace: Leaves) {

		if (Map[TmpSpace].Num() < 2)
			Result.Add(TmpSpace);
		
	}
	return Result;
}

int GraphSpaces::GetDepth(Space* Spc) {
	if(Map[Spc].Num() == 2)
		return 0;
	else
		return 1 + GetDepth(Map[Spc][0]->To);	
}*/

