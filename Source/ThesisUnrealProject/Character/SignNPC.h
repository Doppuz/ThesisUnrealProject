// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnInteractiveClass.h"
#include "SignNPC.generated.h"

class ADoor;

/**
 * 
 */
UCLASS()
class THESISUNREALPROJECT_API ASignNPC : public APawnInteractiveClass
{
	GENERATED_BODY()

public:

	ASignNPC();

	virtual void Choice(int Answer);

	UPROPERTY()
	ADoor* DoorLeft1;
};