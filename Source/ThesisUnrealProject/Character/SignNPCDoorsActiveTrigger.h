// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnInteractiveClass.h"
#include "SignNPCDoors.h"
#include "SignNPCDoorsActiveTrigger.generated.h"

class ATrigger;

/**
 * 
 */
UCLASS()
class THESISUNREALPROJECT_API ASignNPCDoorsActiveTrigger : public ASignNPCDoors
{
	GENERATED_BODY()

public:

	ASignNPCDoorsActiveTrigger();

	virtual void Choice(int Answer) override;

	UPROPERTY(EditAnywhere, Category = "Trigger")
	ATrigger* TriggerActor;

};
