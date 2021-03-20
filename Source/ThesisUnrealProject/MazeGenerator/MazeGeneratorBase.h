// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <vector>
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MazeGeneratorBase.generated.h"

class AMazeCell;
class RoomMaze;

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
	int Height = 10;

	UPROPERTY(EditAnywhere, Category = "MazeGeneration")
	int MazeObstacle = 0;

	UPROPERTY(EditAnywhere, Category = "MazeGeneration")
	int Maze2Room = 4;
	UPROPERTY(EditAnywhere, Category = "MazeGeneration")
	int Maze3Room = 0;
	UPROPERTY(EditAnywhere, Category = "MazeGeneration")
	int Maze4Room = 0;

	UPROPERTY(EditAnywhere, Category = "MazeGeneration")
	TSubclassOf<AMazeCell> CellClass;

	TArray<TArray<AMazeCell*>> *Maze = nullptr;
	TArray<RoomMaze> *Rooms = nullptr;
	int NumberOfCells = (Length*Height) - MazeObstacle - 2 * Maze2Room - 3 * Maze3Room - 4 * Maze4Room;

	//Methods
	void PrintMaze();
	void InitializeMaze();
	void CreateObstacle(int ObstaclesNumber);
	void CreateRooms();
	void CreateRoomSize2();
	void CheckRoomIntersection(int Row, int Column, bool& bIntersection);
	void RoomWallHide(TArray<AMazeCell*>& Room,int rowExtr, int columnExtr, int Pos);
	void CreateMazeWrapper(int i, int j, int& CellProcessed);
	void CheckForNeighbors(TArray<AMazeCell*>& neighbors,int i,int j);
	void CreateMaze();
};
