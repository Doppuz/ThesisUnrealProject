// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Node.h"
#include "CoreMinimal.h"

class AMazeCell;

//template<typename F>
class THESISUNREALPROJECT_API Side{
public:
	Side(AMazeCell* From,AMazeCell* To, float Weight);
	~Side();

	AMazeCell* From;
	AMazeCell* To;
	float Weight;
};
