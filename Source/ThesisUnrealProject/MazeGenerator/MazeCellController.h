// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class THESISUNREALPROJECT_API MazeCellController
{
public:
	MazeCellController(int PosX,int PosY);
	~MazeCellController();

	bool IsObstacle = false;
	bool IsVisited = false;
	bool LeftWall = true;
	bool RightWall = true;
	bool UpWall = true;
	bool DownWall = true;
	int PosX;
	int PosY;

	FString PrintCell();
};
