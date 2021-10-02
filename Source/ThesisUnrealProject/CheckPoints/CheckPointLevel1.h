// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Checkpoint.h"
#include "CheckPointLevel1.generated.h"

/**
 * 
 */
UCLASS()
class THESISUNREALPROJECT_API ACheckPointLevel1 : public ACheckpoint{

	GENERATED_BODY()

public:

	virtual void OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit);
	
};
