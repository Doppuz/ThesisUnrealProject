// Fill out your copyright notice in the Description page of Project Settings.

#include "MazeGeneratorBase.h"
#include "MazeCellController.h"
#include "MazeCellActor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMazeGeneratorBase::AMazeGeneratorBase(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMazeGeneratorBase::BeginPlay(){
	Super::BeginPlay();
	
	std::vector<std::vector<MazeCellController>> TempMaze(length,std::vector<MazeCellController>(heigth));
	Maze = &TempMaze;

	//UE_LOG(LogTemp,Warning, TEXT("%i"), a[0][0]);
	//Maze = &TempMaze; 
	//UE_LOG(LogTemp,Warning, TEXT("Start the generation of the maze %i %i"), length, heigth);

	createObstacle(10);
	printMaze();

	FVector Origin(0,0,0);
	FRotator Rotation(0,0,0);
	FTransform SpawnTransform(Rotation, Origin);

	AMazeCellActor* MyDeferredActor = Cast<AMazeCellActor>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, CellClass, SpawnTransform));
	if (MyDeferredActor != nullptr){
    	MyDeferredActor->Init(Three_Wall);
 
    	UGameplayStatics::FinishSpawningActor(MyDeferredActor, SpawnTransform);
	}else{
		UE_LOG(LogTemp,Warning, TEXT("Null"));
	}
	//AMazeCellActor* wall = GetWorld()->SpawnActor<AMazeCellActor>(CellClass,Origin,Rotation);
}

// Called every frame
void AMazeGeneratorBase::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
	
}

void AMazeGeneratorBase::printMaze(){
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

void AMazeGeneratorBase::createObstacle(int Obstacles){
	std::vector<int> AlreadySelectedNumbers(0);

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
	}	
}

void AMazeGeneratorBase::createRoom() {
	
}


