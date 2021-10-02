// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Trigger.h"
#include "TriggerSpawnNight.generated.h"

class AAICharacterPawnQuad;

UCLASS()
class THESISUNREALPROJECT_API ATriggerSpawnNight : public ATrigger
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATriggerSpawnNight();

	UPROPERTY(EditAnywhere,  Category = "SpawnAlly")
	TSubclassOf<AAICharacterPawnQuad> AllyClass;
	
	//check if the trigger switch on or of fthe light.
	UPROPERTY(EditAnywhere, Category = "Light")
	float AttenuationRadius;


protected:

	virtual void OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit);

	//check if the trigger switch on or of fthe light.
	UPROPERTY(EditAnywhere, Category = "Light")
	bool LightOn;

};
