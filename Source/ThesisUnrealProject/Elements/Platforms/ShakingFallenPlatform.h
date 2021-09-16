// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FallenPlatform.h"
#include "ShakingFallenPlatform.generated.h"

UCLASS()
class THESISUNREALPROJECT_API AShakingFallenPlatform : public AFallenPlatform{

	GENERATED_BODY()

public:	

	AShakingFallenPlatform(); 

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Shake speed.
	UPROPERTY(EditAnywhere, Category = "Shake")
	float ShakeRotation;

	//True if it is shaking, false otherwise.
	bool bIsShaking;

	//True if it is shaking, false otherwise.
	bool bStopShaking;

	//Time beetween start and end shake.
	UPROPERTY(EditAnywhere, Category = "Shake")
	float IntervalTime;

	FTimerHandle ShakeTimer;

	//Shake and wait shake used with the timer to change from shaking to not shaking.
	virtual void EnableShake();

	virtual void WaitShake();

	//Used to currently move the actor
	virtual void Shake(float);
	
	FVector StartPos;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};
