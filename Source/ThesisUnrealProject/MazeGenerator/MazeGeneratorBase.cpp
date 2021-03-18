// Fill out your copyright notice in the Description page of Project Settings.

#include "MazeGeneratorBase.h"
#include "MazeCell.h"
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
	Maze = new TArray<TArray<AMazeCell*>>();
	Stack = new TArray<AMazeCell*>();

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
	for(int i=0; i < Heigth; i++){
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
	for(int i = 0; i < Heigth; i++){
		TArray<AMazeCell*> Row;
		for(int j = 0; j < Length; j++){
			FVector Origin(i*(-700),j*700,0);
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
		
		int numExtr = FMath::RandRange(0,(Heigth * Length) - 1);
		
		if(std::find(AlreadySelectedNumbers.begin(), AlreadySelectedNumbers.end(),
			numExtr) == AlreadySelectedNumbers.end()){
		
			//It doesn't worll for Legth != Heigth
			int row = (int) numExtr / Length;
			int column = numExtr % Heigth;
			(*Maze)[row][column]->bIsObstacle = true;
			(*Maze)[row][column]->bIsVisited = true;
			(*Maze)[row][column]->HideObstacleWall();
			AlreadySelectedNumbers.push_back(numExtr);
		
		}else
			i -= 1;
	}	
}

void AMazeGeneratorBase::CreateRoom() {
	
}

//Wrapper for recursion depth visit
void AMazeGeneratorBase::CreateMazeWrapper(int I, int J) {
	TArray<AMazeCell*> Neighbors;
	(*Maze)[I][J]->bIsVisited = true;
	CheckForNeighbors(Neighbors,I,J);
	while(Neighbors.Num() != 0){	
		int numExtr = FMath::RandRange(0,Neighbors.Num() - 1);
		
		//Delete the wall from the 2 cells.
		if(I != Neighbors[numExtr]->I)
			if(I > Neighbors[numExtr]->I){
				(*Maze)[I][J]->HideWall(1);
				(*Maze)[I - 1][J]->HideWall(3);
			}else{
				(*Maze)[I][J]->HideWall(3);
				(*Maze)[I + 1][J]->HideWall(1);
			} 
		else{
			if(J > Neighbors[numExtr]->J){
				(*Maze)[I][J]->HideWall(4);
				(*Maze)[I][J - 1]->HideWall(2);
			}else{
				(*Maze)[I][J]->HideWall(2);
				(*Maze)[I][J + 1]->HideWall(4);
			}  
		}

		CreateMazeWrapper(Neighbors[numExtr]->I,Neighbors[numExtr]->J);
		Neighbors.Empty();
		CheckForNeighbors(Neighbors,I,J);
	}
}

//Start the maze creation from (0,0)
void AMazeGeneratorBase::CreateMaze() {
	int Row = 0;
	int Column = 0;
	//Stack->Push((*Maze)[0][0]);
	//(*Maze)[0][0]->bIsVisited = true;
	CreateMazeWrapper(0,0);
}

void AMazeGeneratorBase::CheckForNeighbors(TArray<AMazeCell*>& Neighbors,int i,int j){
	if(i != 0 && !(*Maze)[i - 1][j]->bIsVisited) Neighbors.Push((*Maze)[i - 1][j]);
	if(i != 19 && !(*Maze)[i + 1][j]->bIsVisited) Neighbors.Push((*Maze)[i + 1][j]);
	if(j != 0 && !(*Maze)[i][j - 1]->bIsVisited) Neighbors.Push((*Maze)[i][j - 1]);
	if(j != 19 && !(*Maze)[i][j + 1]->bIsVisited) Neighbors.Push((*Maze)[i][j + 1]);
}
