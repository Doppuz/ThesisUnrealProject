// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveGameLevel1.generated.h"

class AMaze;

USTRUCT() struct FArrayTransform{

    GENERATED_BODY()
	
	UPROPERTY()
	TArray<FTransform> Transforms;

};

UCLASS()
class THESISUNREALPROJECT_API USaveGameLevel1 : public USaveGame{

	GENERATED_BODY()

public:
	
	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	TMap<int, FArrayTransform> MazeTransformMap;
	
};
