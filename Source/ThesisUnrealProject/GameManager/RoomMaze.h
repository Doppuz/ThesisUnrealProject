// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MazeCell.h"

/**
 * 
 */
class THESISUNREALPROJECT_API RoomMaze{
public:
	RoomMaze(TArray<AMazeCell*>);
	~RoomMaze();

	bool bDoor = false;

	TArray<AMazeCell*> Room;
	
};
