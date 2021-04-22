// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "CustomGameState.generated.h"

/**
 * 
 */
UCLASS()
class THESISUNREALPROJECT_API ACustomGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	ACustomGameState();
	int CoinNumber;
	float MapPercentage;
};
