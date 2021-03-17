// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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
	
	bool IsObstacle = false;
	bool IsVisited = false;
	int I;
	int J;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
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
	USceneComponent* Root;

};
