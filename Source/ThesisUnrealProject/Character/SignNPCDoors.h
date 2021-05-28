// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnInteractiveClass.h"
#include "SignNPC.h"
#include "SignNPCDoors.generated.h"

class ADoor;

/**
 * 
 */
UCLASS()
class THESISUNREALPROJECT_API ASignNPCDoors : public ASignNPC
{
	GENERATED_BODY()

public:

	ASignNPCDoors();

	virtual void Choice(int Answer) override;

	UPROPERTY(EditAnywhere, Category = "Doors")
	TArray<int> LeftDoors;

	UPROPERTY(EditAnywhere, Category = "Doors")
	TArray<int> RightDoors;

};
