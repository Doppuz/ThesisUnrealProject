// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Trigger.h"
#include "TriggerEndGame.generated.h"

UCLASS()
class THESISUNREALPROJECT_API ATriggerEndGame : public ATrigger
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATriggerEndGame();

protected:

	virtual void OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit);

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> UIEndGame;

};
