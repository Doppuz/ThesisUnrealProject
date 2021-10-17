// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Checkpoint.h"
#include "SaveGameLevel1.h"
#include "CheckPointLevel1.generated.h"

class AMazeManager;

UCLASS()
class THESISUNREALPROJECT_API ACheckPointLevel1 : public ACheckpoint{

	GENERATED_BODY()

public:

	ACheckPointLevel1();

	UPROPERTY(EditAnywhere)
	AMazeManager* MazeManager;

	UPROPERTY(EditAnywhere)
	USceneComponent* SpawnPos;

	virtual void OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit);
	
private:

	TArray<FTransform> CreateTransformArray(UInstancedStaticMeshComponent* MeshInstances);

	TArray<FSpeech> CreateSpeech(TArray<TArray<FString>> List);

};
