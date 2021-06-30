// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "../CustomGameState.h"
#include "SaveGameData.generated.h"

/**
 * 
 */
UCLASS()
class THESISUNREALPROJECT_API USaveGameData : public USaveGame{
	
	GENERATED_BODY()

public: 
	
	USaveGameData();

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	FVector PlayerLocation;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	float Achiever;
	
	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	float Killer;
	
	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	float Explorer;
	
	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	float Socializer;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	float AchieverQ;
	
	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	float KillerQ;
	
	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	float ExplorerQ;
	
	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	float SocializerQ;
	
	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	TArray<FName> Levels;

};
