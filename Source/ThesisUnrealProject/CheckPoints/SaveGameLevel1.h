// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveGameLevel1.generated.h"

class AMaze;
class AGenericDestructibleElements;

//Value to be saved to restore the maze actor.
USTRUCT() struct FMazeValue{

    GENERATED_BODY()

	UPROPERTY()
	FVector Position;
	
	UPROPERTY()
	TArray<FTransform> TransformsFloor;

	UPROPERTY()
	TArray<FTransform> TransformsWall;
	
	UPROPERTY()
	TArray<FTransform> TransformsObstacle;

};

USTRUCT() struct FGeneralActor{

    GENERATED_BODY()

	UPROPERTY()
	FVector Position;
	
	UPROPERTY()
	TSubclassOf<AActor> ActorClass;

};

UCLASS()
class THESISUNREALPROJECT_API USaveGameLevel1 : public USaveGame{

	GENERATED_BODY()

public:
	
	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	TMap<int, FMazeValue> MazeTransformMap;
	
	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	TArray<FGeneralActor> DestructibleElem;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	TArray<FGeneralActor> CoinElem;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	TArray<FGeneralActor> TrapElem;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	TArray<FGeneralActor> HatElem;
	
	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	TArray<FGeneralActor> HeartElem;
	
	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	TArray<FGeneralActor> FallenPlatformElem;

};
