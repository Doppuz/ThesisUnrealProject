// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Trigger.h"
#include "TriggerMap.generated.h"

/**
 * 
 */
UCLASS()
class THESISUNREALPROJECT_API ATriggerMap : public ATrigger{

	GENERATED_BODY()

public:

	virtual void OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit);

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
