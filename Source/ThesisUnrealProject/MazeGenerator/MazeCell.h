// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoupleStruct.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MazeCell.generated.h"

UCLASS()
class THESISUNREALPROJECT_API AMazeCell : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMazeCell();
	
	bool bIsObstacle = false;
	bool bIsVisited = false;
	int NumberRoom = -1;

	//Number of walls
	int WallNumbers = 4;

	//Used to keep trace of the only hidden wall in cell with 3 walls.
	int LastHiddenWall;

	UPROPERTY(VisibleAnywhere, Category = "MazeInformation")
	int I;
	UPROPERTY(VisibleAnywhere, Category = "MazeInformation")
	int J;

	//Methods
	void HideObstacleWall();
	void HideWall(int WallNumber);
	bool HideWallBool(int WallNumber, Coord& OppositeCell,int& WallToDelete);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
	USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxTrigger;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshPlaneComponent;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshWall1Component;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshWall2Component;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshWall3Component;
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshWall4Component;

};
