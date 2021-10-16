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

};
