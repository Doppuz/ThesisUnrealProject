// Fill out your copyright notice in the Description page of Project Settings.

#include "MazeGeneratorBase.h"
#include "MazeCell.h"
#include "Kismet/GameplayStatics.h"
#include "Containers/Array.h"
#include "RoomMaze.h"


// Sets default values
AMazeGeneratorBase::AMazeGeneratorBase(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

AMazeGeneratorBase::~AMazeGeneratorBase() 
{
	delete Maze;
	delete Rooms;
}

// Called when the game starts or when spawned
void AMazeGeneratorBase::BeginPlay(){
	Super::BeginPlay();
	
	//Maze = new std::vector<std::vector<MazeCellController>>(length,std::vector<MazeCellController>(heigth));
	Maze = new TArray<TArray<AMazeCell*>>();
	Rooms = new TArray<RoomMaze>();

	InitializeMaze();
	
	//CreateObstacle(MazeObstacle);
	CreateRooms();
	CreateMaze();
	
	//UE_LOG(LogTemp,Warning, TEXT("%i"), a[0][0]);
	//Maze = &TempMaze; 
	//UE_LOG(LogTemp,Warning, TEXT("Start the generation of the maze %i %i"), length, heigth);

	PrintMaze();
}

// Called every frame
void AMazeGeneratorBase::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
	
}

void AMazeGeneratorBase::PrintMaze(){
	FString row;
	for(int i=0; i < Height; i++){
		row = "";
		UE_LOG(LogTemp,Warning, TEXT(""));
		for(int j=0; j < Length; j++){
			if((*Maze)[i][j]->bIsObstacle)
				row = row + " $ ";
			else
				row = row + " 0 ";
		}
		UE_LOG(LogTemp,Warning, TEXT("%s"), *row);
	}
}

void AMazeGeneratorBase::InitializeMaze() {
	for(int i = 0; i < Height; i++){
		TArray<AMazeCell*> Row;
		for(int j = 0; j < Length; j++){
			FVector Origin(i*(-1100),j*1100,0);
			FRotator Rotation(0,0,0);
			AMazeCell* CellActor = GetWorld()->SpawnActor<AMazeCell>(CellClass,Origin,Rotation);
			CellActor->I = i;
			CellActor->J = j;
			Row.Add(CellActor);
		}
		Maze->Add(Row);
	}
}

void AMazeGeneratorBase::CreateObstacle(int Obstacles){
	std::vector<int> AlreadySelectedNumbers(0);

	for(int i = 0; i < Obstacles; i++){
		
		int numExtr = FMath::RandRange(0,(Height * Length) - 1);
		
		if(std::find(AlreadySelectedNumbers.begin(), AlreadySelectedNumbers.end(),
			numExtr) == AlreadySelectedNumbers.end()){
		
			//It doesn't worll for Legth != Heigth
			int row = (int) numExtr / Length;
			int column = numExtr % Height;
			(*Maze)[row][column]->bIsObstacle = true;
			(*Maze)[row][column]->bIsVisited = true;
			(*Maze)[row][column]->HideObstacleWall();
			AlreadySelectedNumbers.push_back(numExtr);
			
		}else
			i -= 1;
	}	
}

void AMazeGeneratorBase::CreateRooms() {
	for (int i = 0; i < Maze2Room; i++)
		CreateRoomSize2();
	
}

void AMazeGeneratorBase::CreateRoomSize2() {
	bool bIntersection;
	int RowExtr;
	int ColumnExtr;
	
	do {
		bIntersection = false;
		RowExtr = FMath::RandRange(0, Length - 2);
		ColumnExtr = FMath::RandRange(0, Height - 2);
		CheckRoomIntersection(RowExtr, ColumnExtr,bIntersection);
	} while (bIntersection);
	
	TArray<AMazeCell*> Room;

	RoomWallHide(Room, RowExtr, ColumnExtr, Rooms->Num());
	RoomMaze m(Room);
	Rooms->Add(m);
}

void AMazeGeneratorBase::CheckRoomIntersection(int Row, int Column,bool& bIntersection){
	if ((*Maze)[Row][Column]->NumberRoom != -1)
		bIntersection = true;
	if ((*Maze)[Row][Column + 1]->NumberRoom != -1)
		bIntersection = true;
	if ((*Maze)[Row + 1][Column]->NumberRoom != -1)
		bIntersection = true;
	if ((*Maze)[Row + 1][Column + 1]->NumberRoom != -1)
		bIntersection = true;
}

void AMazeGeneratorBase::RoomWallHide(TArray<AMazeCell*>& Room,int rowExtr,int columnExtr, int Pos) {
	(*Maze)[rowExtr][columnExtr]->NumberRoom = Pos;
	(*Maze)[rowExtr][columnExtr]->HideWall(2);
	(*Maze)[rowExtr][columnExtr]->HideWall(3);
	Room.Add((*Maze)[rowExtr][columnExtr]);

	(*Maze)[rowExtr][columnExtr + 1]->NumberRoom = Pos;
	(*Maze)[rowExtr][columnExtr + 1]->HideWall(4);
	(*Maze)[rowExtr][columnExtr + 1]->HideWall(3);
	Room.Add((*Maze)[rowExtr][columnExtr + 1]);

	(*Maze)[rowExtr + 1][columnExtr]->NumberRoom = Pos;
	(*Maze)[rowExtr + 1][columnExtr]->HideWall(2);
	(*Maze)[rowExtr + 1][columnExtr]->HideWall(1);
	Room.Add((*Maze)[rowExtr + 1][columnExtr]);

	(*Maze)[rowExtr + 1][columnExtr + 1]->NumberRoom = Pos;
	(*Maze)[rowExtr + 1][columnExtr + 1]->HideWall(4);
	(*Maze)[rowExtr + 1][columnExtr + 1]->HideWall(1);
	Room.Add((*Maze)[rowExtr + 1][columnExtr + 1]);
}

//Wrapper for recursion depth visit
void AMazeGeneratorBase::CreateMazeWrapper(int I, int J, int& CellProcessed) {
	TArray<AMazeCell*> Neighbors;
	if (!(*Maze)[I][J]->bIsVisited)
		CellProcessed += 1;
	(*Maze)[I][J]->bIsVisited = true;
	if((*Maze)[I][J]->NumberRoom == -1){
		CheckForNeighbors(Neighbors,I,J);
		while (Neighbors.Num() != 0) {
			int numExtr = FMath::RandRange(0, Neighbors.Num() - 1);

		//Delete the wall from the 2 cells.
			if (I != Neighbors[numExtr]->I)
				if (I > Neighbors[numExtr]->I) {
					(*Maze)[I][J]->HideWall(1);
					(*Maze)[I - 1][J]->HideWall(3);
				}
				else {
					(*Maze)[I][J]->HideWall(3);
					(*Maze)[I + 1][J]->HideWall(1);
				}
			else {
				if (J > Neighbors[numExtr]->J) {
					(*Maze)[I][J]->HideWall(4);
					(*Maze)[I][J - 1]->HideWall(2);
				}
				else {
					(*Maze)[I][J]->HideWall(2);
					(*Maze)[I][J + 1]->HideWall(4);
				}
			}

		CreateMazeWrapper(Neighbors[numExtr]->I, Neighbors[numExtr]->J, CellProcessed);
		Neighbors.Empty();
		CheckForNeighbors(Neighbors, I, J);
		}
	}
	else
		(*Rooms)[(*Maze)[I][J]->NumberRoom].bDoor = true;
}

//Start the maze creation from (0,0)
void AMazeGeneratorBase::CreateMaze() {
	int CellProcessed = 0;
	while (CellProcessed != NumberOfCells) {
		int RowExtr = FMath::RandRange(0, Length - 1);
		int ColumnExtr = FMath::RandRange(0, Height - 1);
		CreateMazeWrapper(RowExtr, ColumnExtr, CellProcessed);
		UE_LOG(LogTemp,Warning, TEXT("C = %i N = %i"), CellProcessed, NumberOfCells);
	}
}

void AMazeGeneratorBase::CheckForNeighbors(TArray<AMazeCell*>& Neighbors,int i,int j){
	if(i != 0 && !(*Maze)[i - 1][j]->bIsVisited &&
		((*Maze)[i - 1][j]->NumberRoom == -1 || !(*Rooms)[(*Maze)[i - 1][j]->NumberRoom].bDoor))
		Neighbors.Push((*Maze)[i - 1][j]);

	if(i != (Length - 1) && !(*Maze)[i + 1][j]->bIsVisited &&
		((*Maze)[i + 1][j]->NumberRoom == -1 || !(*Rooms)[(*Maze)[i + 1][j]->NumberRoom].bDoor))
		Neighbors.Push((*Maze)[i + 1][j]);

	if(j != 0 && !(*Maze)[i][j - 1]->bIsVisited &&
		((*Maze)[i][j - 1]->NumberRoom == -1 || !(*Rooms)[(*Maze)[i][j - 1]->NumberRoom].bDoor))
		Neighbors.Push((*Maze)[i][j - 1]);

	if(j != (Length - 1) && !(*Maze)[i][j + 1]->bIsVisited &&
		((*Maze)[i][j + 1]->NumberRoom == -1 || !(*Rooms)[(*Maze)[i][j + 1]->NumberRoom].bDoor))
		Neighbors.Push((*Maze)[i][j + 1]);
}
