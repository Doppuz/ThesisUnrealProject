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
	int MazeObstacle = 10;

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
	TArray<AMazeCell*> Passed;
	TArray<TArray<AMazeCell*>> TempMaze;
	int NumberOfCells;

	//Methods
	void PrintMaze();
	void InitializeMaze();
	void CreateObstacle(int ObstaclesNumber);
	void CreateRooms();
	void CreateDoor(TArray<AMazeCell*>);
	void CreateRoomSize2();
	bool CheckRoomIntersection(int Row, int Column);
	bool CheckNearbyRoom(int Row, int Column, int RoomSize);
	bool CheckNearbyRoomWrapper(int Row, int Column, int RoomSize, int Side);
	void RoomWallHide(TArray<AMazeCell*>& Room,int rowExtr, int columnExtr, int Pos);
	void CreateMazeWrapper(int i, int j, int& CellProcessed);
	void CheckForNeighbors(TArray<AMazeCell*>& neighbors,int i,int j);
	void CreateMaze();
};
