// Fill out your copyright notice in the Description page of Project Settings.

#include "MazeGeneratorBase.h"
#include "MazeCell.h"

// Sets default values
AMazeGeneratorBase::AMazeGeneratorBase(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMazeGeneratorBase::BeginPlay(){
	Super::BeginPlay();
	
	//std::vector<std::vector<ABo>> TempMaze(length,std::vector<ABo>(heigth));
	TArray<AMazeCell*> a;
	//a.Init(10,5);
	TArray<TArray<AMazeCell>> b;
	//b.Add(a);
	//b[0][0] = 2;
	AMazeCell cell;
	for(int i = 0; i < heigth; i++){
		for(int j = 0; j < length; j++){
			//a.Add(&cell);
		}	
	}

	//UE_LOG(LogTemp,Warning, TEXT("%i"), a[0][0]);
	//Maze = &TempMaze; 
	//UE_LOG(LogTemp,Warning, TEXT("Start the generation of the maze %i %i"), length, heigth);

	//createObstacle(100);
	//printMaze();

	/*FVector p(0,0,0);
	FRotator p2(0,0,0);
	
	AActor* wall = GetWorld()->SpawnActor<AActor>(One_Wall,p,p2);*/
}

// Called every frame
void AMazeGeneratorBase::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
	
}

void AMazeGeneratorBase::printMaze(){
/*	FString row;
	for(int i=0; i < heigth; i++){
		row = "";
		UE_LOG(LogTemp,Warning, TEXT(""));
		for(int j=0; j < length; j++){
			//row = row + (*Maze)[i][j].PrintCell() + " ";
		}
		UE_LOG(LogTemp,Warning, TEXT("%s"), *row);
	}*/
}

void AMazeGeneratorBase::createObstacle(int Obstacles){
	/*std::vector<int> AlreadySelectedNumbers(0);

	for(int i = 0; i < Obstacles; i++){
		
		int numExtr = FMath::RandRange(0,99);
		
		if(std::find(AlreadySelectedNumbers.begin(), AlreadySelectedNumbers.end(),
			numExtr) == AlreadySelectedNumbers.end()){
		
			int row = (int) numExtr / length;
			int column = numExtr % length;
			(*Maze)[row][column].IsObstacle = true;
			AlreadySelectedNumbers.push_back(numExtr);
		
		}else
			i -= 1;
	}	*/
}

void AMazeGeneratorBase::createRoom() {
	
}


