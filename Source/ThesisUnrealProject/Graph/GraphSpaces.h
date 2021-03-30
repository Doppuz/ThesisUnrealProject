// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Space.h"
#include "Graph.h"
#include "CoreMinimal.h"

/**
 * 
 */
class THESISUNREALPROJECT_API GraphSpaces : public Graph{
public:
	GraphSpaces();
	~GraphSpaces();

	TArray<Node*> GetLeaves(float RoomLimit);
	TArray<Node*> GetLeavesNoSpace();

};
