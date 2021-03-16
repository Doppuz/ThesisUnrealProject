// Fill out your copyright notice in the Description page of Project Settings.

#include "MazeGeneratorBase.h"
#include "MazeCellController.h"
#include "MazeCellActor.h"
#include "Kismet/GameplayStatics.h"
#include "Containers/Array.h"

// Sets default values
AMazeGeneratorBase::AMazeGeneratorBase(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

AMazeGeneratorBase::~AMazeGeneratorBase() 
{
	delete Maze;
	delete Stack;
}

// Called when the game starts or when spawned
void AMazeGeneratorBase::BeginPlay(){
	Super::BeginPlay();
	
	//Maze = new std::vector<std::vector<MazeCellController>>(length,std::vector<MazeCellController>(heigth));
	Maze = new TArray<TArray<MazeCellController>>();
	Stack = new TArray<MazeCellController>();

	InitializeMaze();
	CreateObstacle(10);
	
	CreateMaze();
	
	//UE_LOG(LogTemp,Warning, TEXT("%i"), a[0][0]);
	//Maze = &TempMaze; 
	//UE_LOG(LogTemp,Warning, TEXT("Start the generation of the maze %i %i"), length, heigth);

	PrintMaze();

	/*FVector Origin(0,0,0);
	FRotator Rotation(0,0,0);
	FTransform SpawnTransform(Rotation, Origin);

	AMazeCellActor* MyDeferredActor = Cast<AMazeCellActor>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, CellClass, SpawnTransform));
	if (MyDeferredActor != nullptr){
    	MyDeferredActor->Init(Three_Wall);
 
    	UGameplayStatics::FinishSpawningActor(MyDeferredActor, SpawnTransform);
	}else{
		UE_LOG(LogTemp,Warning, TEXT("Null"));
	}*/
	//AMazeCellActor* wall = GetWorld()->SpawnActor<AMazeCellActor>(CellClass,Origin,Rotation);
}

// Called every frame
void AMazeGeneratorBase::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
	
}

void AMazeGeneratorBase::PrintMaze(){
	FString row;
	for(int i=0; i < heigth; i++){
		row = "";
		UE_LOG(LogTemp,Warning, TEXT(""));
		for(int j=0; j < length; j++){
			row = row + (*Maze)[i][j].PrintCell() + " ";
		}
		UE_LOG(LogTemp,Warning, TEXT("%s"), *row);
	}
}

void AMazeGeneratorBase::InitializeMaze() {
	for(int i = 0; i < heigth; i++){
		TArray<MazeCellController> Row;
		for(int j = 0; j < length; j++){
			Row.Add(MazeCellController(j,i));
		}
		Maze->Add(Row);
	}
}

void AMazeGeneratorBase::CreateObstacle(int Obstacles){
	std::vector<int> AlreadySelectedNumbers(0);

	for(int i = 0; i < Obstacles; i++){
		
		int numExtr = FMath::RandRange(0,99);
		
		if(std::find(AlreadySelectedNumbers.begin(), AlreadySelectedNumbers.end(),
			numExtr) == AlreadySelectedNumbers.end()){
		
			int row = (int) numExtr / length;
			int column = numExtr % length;
			(*Maze)[row][column].IsObstacle = true;
			(*Maze)[row][column].IsVisited = true;
			AlreadySelectedNumbers.push_back(numExtr);
		
		}else
			i -= 1;
	}	
}

void AMazeGeneratorBase::CreateRoom() {
	
}

//Wrapper for recursion depth visit
void AMazeGeneratorBase::CreateMazeWrapper(int Y, int X) {
	TArray<MazeCellController> Neighbors;
	(*Maze)[X][Y].IsVisited = true;
	CheckForNeighbors(Neighbors,X,Y);
	while(Neighbors.Num() != 0){
		int numExtr = FMath::RandRange(0,Neighbors.Num() - 1);
		
		//Delete the wall from the 2 cells.
		if(Y != Neighbors[numExtr].PosY)
			if(Y > Neighbors[numExtr].PosY){
				(*Maze)[Y][X].UpWall = false;
				(*Maze)[Y - 1][X].DownWall = false;
			}else{
				(*Maze)[Y][X].DownWall = false;
				(*Maze)[Y + 1][X].UpWall = false;
			} 
		else{
			if(X > Neighbors[numExtr].PosX){
				(*Maze)[Y][X].LeftWall = false;
				(*Maze)[Y][X - 1].RightWall = false;
			}else{
				(*Maze)[Y][X].RightWall = false;
				(*Maze)[Y][X + 1].LeftWall = false;
			}  
		}

		CreateMazeWrapper(Neighbors[numExtr].PosX,Neighbors[numExtr].PosY);
		Neighbors.RemoveAt(numExtr);
	}
}

//Start the maze creation from (0,0)
void AMazeGeneratorBase::CreateMaze() {
	int Row = 0;
	int Column = 0;
	Stack->Push((*Maze)[0][0]);
	(*Maze)[0][0].IsVisited = true;
	CreateMazeWrapper(0,0);
}

void AMazeGeneratorBase::CheckForNeighbors(TArray<MazeCellController>& Neighbors,int i,int j){
	if(i != 0 && !(*Maze)[i - 1][j].IsVisited) Neighbors.Push((*Maze)[i - 1][j]);
	if(i != 9 && !(*Maze)[i + 1][j].IsVisited) Neighbors.Push((*Maze)[i + 1][j]);
	if(j != 0 && !(*Maze)[i][j - 1].IsVisited) Neighbors.Push((*Maze)[i][j - 1]);
	if(j != 9 && !(*Maze)[i][j + 1].IsVisited) Neighbors.Push((*Maze)[i][j + 1]);
}
