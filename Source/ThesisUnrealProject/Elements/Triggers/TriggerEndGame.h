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
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit);

	//check if the trigger switch on or of fthe light.
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> UIEndGame;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
