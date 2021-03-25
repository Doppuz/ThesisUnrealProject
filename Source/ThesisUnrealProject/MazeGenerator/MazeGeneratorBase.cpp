// Fill out your copyright notice in the Description page of Project Settings.

#include "MazeGeneratorBase.h"
#include "MazeCell.h"
#include "Kismet/GameplayStatics.h"
#include "Containers/Array.h"
#include "RoomMaze.h"
#include "CoupleStruct.h"


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

	NumberOfCells = (Length*Height) - (MazeObstacle) - 4 * Maze2Room - 9 * Maze3Room - 16 * Maze4Room;
	
	//Maze = new std::vector<std::vector<MazeCellController>>(length,std::vector<MazeCellController>(heigth));
	Maze = new TArray<TArray<AMazeCell*>>();
	Rooms = new TArray<RoomMaze>();

	InitializeMaze();

	CreateObstacle(MazeObstacle);
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
			FVector Origin(i*(-1100) * 1.5 ,j*1100 * 1.5,0);
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
	int RowExtr, ColumnExtr;

	for(int i = 0; i < Obstacles; i++){
		
		RowExtr = FMath::RandRange(0, Length - 1);
		ColumnExtr = FMath::RandRange(0, Height - 1);
		
		if(std::find(AlreadySelectedNumbers.begin(), AlreadySelectedNumbers.end(),
			(RowExtr + 1) * (ColumnExtr + 1)) == AlreadySelectedNumbers.end() &&
			(*Maze)[RowExtr][ColumnExtr]->NumberRoom == -1){
		
			//It doesn't worll for Legth != Heigth
			(*Maze)[RowExtr][ColumnExtr]->bIsObstacle = true;
			(*Maze)[RowExtr][ColumnExtr]->bIsVisited = true;
			(*Maze)[RowExtr][ColumnExtr]->HideObstacleWall();
			AlreadySelectedNumbers.push_back((RowExtr + 1) * (ColumnExtr + 1));
			Passed.Add((*Maze)[RowExtr][ColumnExtr]);
			
		}else
			i -= 1;
	}	
}

void AMazeGeneratorBase::CreateRooms() {
	for (int i = 0; i < Maze2Room; i++)
		CreateRoomSize2();
	
}

void AMazeGeneratorBase::CreateRoomSize2() {
	int RowExtr;
	int ColumnExtr;
	
	do {
		RowExtr = FMath::RandRange(0, Length - 2);
		ColumnExtr = FMath::RandRange(0, Height - 2);
	} while (CheckRoomIntersection(RowExtr, ColumnExtr));
	
	TArray<AMazeCell*> Room;

	RoomWallHide(Room, RowExtr, ColumnExtr, Rooms->Num());
	//CreateDoor(Room);
	RoomMaze m(Room);
	Rooms->Add(m);
}

void AMazeGeneratorBase::CreateDoor(TArray<AMazeCell*> Room) {
	int CellExtr;
	int WallExtr;
	Coord OppositeCell;
	int WallToDelete;
	do {
		CellExtr = FMath::RandRange(0, Room.Num() - 1);
		WallExtr = FMath::RandRange(1, 4);
	} while (!Room[CellExtr]->HideWallBool(WallExtr, OppositeCell, WallToDelete));
	(*Maze)[OppositeCell.CoordI][OppositeCell.CoordJ]->HideWall(WallToDelete);
}

bool AMazeGeneratorBase::CheckRoomIntersection(int Row, int Column){

	return (*Maze)[Row][Column]->NumberRoom != -1 || (*Maze)[Row][Column + 1]->NumberRoom != -1 ||
		(*Maze)[Row + 1][Column]->NumberRoom != -1 || (*Maze)[Row + 1][Column + 1]->NumberRoom != -1 ||
		(*Maze)[Row][Column]->bIsObstacle || (*Maze)[Row][Column + 1]->bIsObstacle ||
		(*Maze)[Row + 1][Column]->bIsObstacle || (*Maze)[Row + 1][Column + 1]->bIsObstacle;
}

void AMazeGeneratorBase::RoomWallHide(TArray<AMazeCell*>& Room,int rowExtr,int columnExtr, int Pos) {
	int FirstIndice;
	int SecondIndice;

	for(int i = 0; i < 2; i++){
		SecondIndice = i == 0 ? 3 : 1;
		for(int j = 0; j < 2; j++){
			FirstIndice = (j + 1) * 2;
			(*Maze)[rowExtr + i][columnExtr + j]->NumberRoom = Pos;
			(*Maze)[rowExtr + i][columnExtr + j]->HideWall(FirstIndice);
			(*Maze)[rowExtr + i][columnExtr + j]->HideWall(SecondIndice);
			Room.Add((*Maze)[rowExtr + i][columnExtr + j]);
			//if(!Passed.Contains((*Maze)[rowExtr + i][columnExtr + j]))
			Passed.Add((*Maze)[rowExtr + i][columnExtr + j]);
		}
	}
}

//Wrapper for recursion depth visit
void AMazeGeneratorBase::CreateMazeWrapper(int I, int J, int& CellProcessed) {
	TArray<AMazeCell*> Neighbors;
	//if (!(*Maze)[I][J]->bIsVisited && (*Maze)[I][J]->NumberRoom == -1 && !(*Maze)[I][J]->bIsObstacle)
	//	CellProcessed += 1;
	if(!Passed.Contains((*Maze)[I][J]))
		Passed.Add((*Maze)[I][J]);
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

	//while (CellProcessed != NumberOfCells) {
	while (Passed.Num() != Length * Length) {
		int RowExtr = FMath::RandRange(0, Length - 1);
		int ColumnExtr = FMath::RandRange(0, Height - 1);
		if(!(*Maze)[RowExtr][ColumnExtr]->bIsObstacle && (*Maze)[RowExtr][ColumnExtr]->NumberRoom == -1)
			CreateMazeWrapper(RowExtr, ColumnExtr, CellProcessed);
		//for (int i = 0; i < (*Rooms).Num(); i++) {
		//	(*Rooms)[i].bDoor = false;
		//}
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
		((*Maze)[i][j - 1]->NumberRoom == -1  || !(*Rooms)[(*Maze)[i][j - 1]->NumberRoom].bDoor))
		Neighbors.Push((*Maze)[i][j - 1]);

	if(j != (Length - 1) && !(*Maze)[i][j + 1]->bIsVisited &&
		((*Maze)[i][j + 1]->NumberRoom == -1 || !(*Rooms)[(*Maze)[i][j + 1]->NumberRoom].bDoor))
		Neighbors.Push((*Maze)[i][j + 1]);
}