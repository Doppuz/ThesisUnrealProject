// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Trigger.h"
#include "TriggerSpawnAlly.generated.h"

class AAICharacterPawnQuad;

UCLASS()
class THESISUNREALPROJECT_API ATriggerSpawnAlly : public ATrigger
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATriggerSpawnAlly();

	virtual void OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit);

	UPROPERTY(EditAnywhere,  Category = "SpawnAlly")
	TSubclassOf<AAICharacterPawnQuad> AllyClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
