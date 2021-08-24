// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Maze.generated.h"

UCLASS()
class THESISUNREALPROJECT_API AMaze : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMaze();

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	UInstancedStaticMeshComponent* FloorInstances;

	UPROPERTY(VisibleAnywhere)
	UInstancedStaticMeshComponent* WallInstances;

	void CreateFloor(FTransform);

	void CreateWalls(FTransform);

	void CreateHorizontalWall(FTransform);
	
	void CreateVerticalWall(FTransform);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float MeshLenght;


};
