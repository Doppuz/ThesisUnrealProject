// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <vector>
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Graph/Graph.h"

class AMazeCell;
class RoomMaze;
/**
 * 
 */
class THESISUNREALPROJECT_API MazeGenerationCreation
{
public:
	MazeGenerationCreation(int Length, int Height, int MazeObstacle, int Maze2Room, TSubclassOf<AMazeCell> CellClass,
		TArray<TArray<AMazeCell*>> *Maze, TArray<RoomMaze> *Rooms, Graph* MazeGraph,
		UWorld* World);
	~MazeGenerationCreation();

	void StandardMazeCreation();

private:
	//Methods

	void PrintMaze();
	void InitializeMaze();
	void CreateObstacle(int ObstaclesNumber);
	void CreateRooms();
	void CreateRoomSize2();
	bool CheckRoomIntersection(int Row, int Column);
	bool CheckNearbyRoom(int Row, int Column, int RoomSize);
	bool CheckNearbyRoomWrapper(int Row, int Column, int RoomSize, int Side);
	void RoomWallHide(TArray<AMazeCell*>& Room,int rowExtr, int columnExtr, int Pos);
	void CreateMazeWrapper(int i, int j, int& CellProcessed);
	void CheckForNeighbors(TArray<AMazeCell*>& neighbors,int i,int j);
	void CreateMaze();

	//Just take the parameter from the Maze Manager class
	int Length;
	int Height;
	int MazeObstacle;
	int Maze2Room;
	int Maze3Room;
	int Maze4Room;
	TSubclassOf<AMazeCell> CellClass;

	TArray<TArray<AMazeCell*>> *Maze = nullptr;
	TArray<RoomMaze> *Rooms = nullptr;
	//TempMaze
	TArray<TArray<AMazeCell*>> TempMaze;
	Graph* MazeGraph;

	UWorld* World;
};
