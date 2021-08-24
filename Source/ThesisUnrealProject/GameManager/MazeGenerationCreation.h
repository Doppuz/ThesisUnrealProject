// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <vector>
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Graph/Graph.h"

//class AMazeCell;
class RoomMaze;
/**
 * 
 */
class THESISUNREALPROJECT_API MazeGenerationCreation
{
public:
	/*MazeGenerationCreation(int Length, int Height, int MazeObstacle, int Maze2Room, TSubclassOf<AMazeCell> CellClass,
		TArray<TArray<AMazeCell*>> *Maze, TArray<RoomMaze> *Rooms, Graph* MazeGraph,
		UWorld* World, float);
	~MazeGenerationCreation();

	void StandardMazeCreation();

	void PrintMaze();
	
	TArray<RoomMaze> *Rooms = nullptr;

private:
	//Methods

	void InitializeMaze();
	void CreateObstacle(int ObstaclesNumber);
	void CreateRooms();
	void CreateRoomSize2();
	void CreateRoomSize3();
	bool CheckRoomIntersection(int Row, int Column, int RoomSize);
	bool CheckNearbyRoom(int Row, int Column, int RoomSize);
	void RoomWallHide(TArray<AMazeCell*>& Room, int rowExtr, int columnExtr, int Pos, int WallsNumber);
	void CreateMazeWrapper(int i, int j);
	void CheckForNeighbors(TArray<AMazeCell*>& neighbors,int i,int j);
	void CreateMaze();

	//Just take the parameter from the Maze Manager class
	int Length;
	int Height;
	int MazeObstacle;
	int Maze2Room;
	int Maze3Room;
	//used to create the maze at a particular depth
	float Depth;
	TSubclassOf<AMazeCell> CellClass;

	TArray<TArray<AMazeCell*>> *Maze = nullptr;
	//TempMaze
	TArray<TArray<AMazeCell*>> TempMaze;
	Graph* MazeGraph;

	UWorld* World;*/
};
