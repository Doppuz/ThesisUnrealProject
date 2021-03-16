// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include <vector>
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MazeGeneratorBase.generated.h"

class MazeCellController;
class AMazeCellActor;

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
	int length = 10;

	UPROPERTY(EditAnywhere, Category = "MazeGeneration")
	int heigth = 10;

	UPROPERTY(EditAnywhere, Category = "MazeGeneration")
	UStaticMesh* One_Wall;

	UPROPERTY(EditAnywhere, Category = "MazeGeneration")
	UStaticMesh* Two_Wall;
	
	UPROPERTY(EditAnywhere, Category = "MazeGeneration")
	UStaticMesh* Three_Wall;
	
	UPROPERTY(EditAnywhere, Category = "MazeGeneration")
	TSubclassOf<AMazeCellActor> CellClass;

	TArray<TArray<MazeCellController>> *Maze = nullptr;
	TArray<MazeCellController> *Stack = nullptr;


	//Methods
	void PrintMaze();
	void InitializeMaze();
	void CreateObstacle(int Obstacles);
	void CreateRoom();
	void CreateMazeWrapper(int i, int j);
	void CheckForNeighbors(TArray<MazeCellController>& neighbors,int i,int j);
	void CreateMaze();
};
