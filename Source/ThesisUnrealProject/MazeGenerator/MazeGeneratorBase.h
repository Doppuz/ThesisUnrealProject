// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include <vector>
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MazeGeneratorBase.generated.h"

class AMazeCell;

UCLASS()
class THESISUNREALPROJECT_API AMazeGeneratorBase : public AActor{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMazeGeneratorBase();
	~AMazeGeneratorBase();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "MazeGeneration")
	int Length = 10;

	UPROPERTY(EditAnywhere, Category = "MazeGeneration")
	int Heigth = 10;

	UPROPERTY(EditAnywhere, Category = "MazeGeneration")
	TSubclassOf<AMazeCell> CellClass;

	TArray<TArray<AMazeCell*>> *Maze = nullptr;
	TArray<AMazeCell*> *Stack = nullptr;


	//Methods
	void PrintMaze();
	void InitializeMaze();
	void CreateObstacle(int Obstacles);
	void CreateRoom();
	void CreateMazeWrapper(int i, int j);
	void CheckForNeighbors(TArray<AMazeCell*>& neighbors,int i,int j);
	void CreateMaze();
};
