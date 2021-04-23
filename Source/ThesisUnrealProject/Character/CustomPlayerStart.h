// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "CustomPlayerStart.generated.h"

/**
 * 
 */
UCLASS()
class THESISUNREALPROJECT_API ACustomPlayerStart : public APlayerStart
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
