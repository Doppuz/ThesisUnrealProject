// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomMaze.h"

RoomMaze::RoomMaze(TArray<AMazeCell*> Room){
	this->Room = Room;
	//UE_LOG(LogTemp, Warning, TEXT("%i"), this->Room[0]->I);
}

RoomMaze::~RoomMaze()
{
}

void RoomMaze::CreateDoors(int DoorsNumber) {
	int CellExtr;
	int WallExtr;
	for (int i = 0; i < DoorsNumber; i++) {
		do {
			CellExtr = FMath::RandRange(0, Room.Num() - 1);
			WallExtr = FMath::RandRange(1, 4);
		} while (!Room[CellExtr]->HideWallBool(WallExtr));
	}
}
