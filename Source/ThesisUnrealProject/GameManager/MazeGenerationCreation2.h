// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <vector>
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Graph/Graph.h"

class AMazeCell2;
class RoomMaze;
class AMaze;
/**
 * 
 */
class THESISUNREALPROJECT_API MazeGenerationCreation2
{
public:
	MazeGenerationCreation2(int Length, int Height, int MazeRooms, TSubclassOf<AMazeCell2> CellClass,
		Graph<AMazeCell2>* MazeGraph, UWorld* World, float,AMaze*);
	~MazeGenerationCreation2();

	void StandardMazeCreation();

	void PrintMaze();
	
	TArray<int> RoomWithDoor;

private:

	//Methods
	void InitializeMaze();
	void CreateObstacle(int ObstaclesNumber);
	void CreateRooms(int);
	bool CheckRoomIntersection(TArray<AMazeCell2*>,int);
	void CreateMaze(AMazeCell2*,AMazeCell2*);

	//Just take the parameter from the Maze Manager class
	int Length;
	int Height;
	int MazeRooms;
	//used to create the maze at a particular depth
	float Depth;
	TSubclassOf<AMazeCell2> CellClass;

	Graph<AMazeCell2>* MazeGraph;

	UWorld* World;

	AMaze* Maze2;

	//Distance between 2 cells.
	float Distance;


};
