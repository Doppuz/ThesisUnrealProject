// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnInteractiveClass.h"
#include "SignNPCDoors.h"
#include "NPCRumbleSpawn.generated.h"

class ARumbleArena;
class ACoinController;

/**
 * 
 */
UCLASS()
class THESISUNREALPROJECT_API ANPCRumbleSpawn : public ASignNPCDoors
{
	GENERATED_BODY()

public:

	ANPCRumbleSpawn();

	virtual void Choice(int Answer);

	UPROPERTY(EditAnywhere)
	ARumbleArena* Arena;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ACoinController> RewardClass;


};
