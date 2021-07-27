// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MazeCell.generated.h"

class AGeneralElem;

USTRUCT(BlueprintType)
struct FPositionRotation{
    
	GENERATED_BODY()

    FVector Position;
	FRotator Rotation;

};

UCLASS()
class THESISUNREALPROJECT_API AMazeCell : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMazeCell();
	
	bool bIsObstacle = false;
	bool bIsVisited = false;
	bool bDynamicIsVisited = false;
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
	FPositionRotation GetWallPosition(int);

	void AddElem(AActor*);
	void RemoveElem(AActor*);
	void RemoveAllElem();

	//Given an adjacent cell, returns the wall beetween the 2 cells. 
	int GiveFrontWall(AMazeCell*);

	void PopulateElem(TSubclassOf<AGeneralElem>);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
	USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere)
	USceneComponent* Meshes;

	UPROPERTY(EditAnywhere)
	USceneComponent* SpawnPoints;

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

	UPROPERTY(EditAnywhere)
	USceneComponent* SpawnPointWall1;

	UPROPERTY(EditAnywhere)
	USceneComponent* SpawnPointWall2;

	UPROPERTY(EditAnywhere)
	USceneComponent* SpawnPointWall3;

	UPROPERTY(EditAnywhere)
	USceneComponent* SpawnPointWall4;

	TArray<int> Walls;

	TArray<AActor*> ObjectsInside;

};
