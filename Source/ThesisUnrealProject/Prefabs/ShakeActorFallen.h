// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShakeActor.h"
#include "ShakeActorFallen.generated.h"

/**
 * 
 */
UCLASS()
class THESISUNREALPROJECT_API AShakeActorFallen : public AShakeActor
{
	GENERATED_BODY()

protected:

	//Used to currently move the actor
	virtual void Shake(float);
	
};
