// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveGameBartle.generated.h"

/**
 * 
 */
UCLASS()
class THESISUNREALPROJECT_API USaveGameBartle : public USaveGame{

	GENERATED_BODY()

public: 

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	float Achiever;
	
	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	float Killer;
	
	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	float Explorer;
	
	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	float Socializer;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	float LastAchiever;
	
	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	float LastKiller;
	
	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	float LastExplorer;
	
	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	float LastSocializer;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	float OldAchiever;
	
	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	float OldKiller;
	
	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	float OldExplorer;
	
	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	float OldSocializer;

};
