// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomMaze.h"

RoomMaze::RoomMaze(TArray<AMazeCell*> Room){
	this->Room = Room;
	//UE_LOG(LogTemp, Warning, TEXT("%i"), this->Room[0]->I);
}

RoomMaze::~RoomMaze()
{
}
