// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnInteractiveClass.h"
#include "NPCEquipment.generated.h"

class ADoor;

/**
 * 
 */
UCLASS()
class THESISUNREALPROJECT_API ANPCEquipment : public APawnInteractiveClass
{
	GENERATED_BODY()

public:

	ANPCEquipment();

	virtual void Choice(int Answer);

	UPROPERTY()
	ADoor* DoorLeft1;
};
