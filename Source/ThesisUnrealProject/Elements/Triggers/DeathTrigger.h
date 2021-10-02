// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Trigger.h"
#include "DeathTrigger.generated.h"

UCLASS()
class THESISUNREALPROJECT_API ADeathTrigger : public ATrigger
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADeathTrigger();

	virtual void OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit) override;

};
