// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Cell.h"
#include "../Graph/GraphSpaces.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpacePartitionMazeGenerator.generated.h"

UCLASS()
class THESISUNREALPROJECT_API ASpacePartitionMazeGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpacePartitionMazeGenerator();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, Category = "MazeGeneration")
	float RoomSizeLimit = 1500000000;

	UPROPERTY(EditAnywhere, Category = "MazeGeneration")
	TSubclassOf<ACell> CellClass;

	float CellSize = 500;

	void CreateMaze();
	void CreateRooms(TArray<Space *>);
	void CreateCorridors();
	void GenerateCorridors(Space*,Space*);
	void DrawLine(FVector Start, FVector End);
	void DrawSquare(float, float, float, float);
	Graph Maze;

};
