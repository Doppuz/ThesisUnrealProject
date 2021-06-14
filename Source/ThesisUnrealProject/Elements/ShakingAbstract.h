// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShakingAbstract.generated.h"

UCLASS(Abstract)
class THESISUNREALPROJECT_API AShakingAbstract : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShakingAbstract();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

#pragma region Shake

	//Shake speed.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shake")
	float ShakeSpeed;

	//Shake Distance
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shake")
	float ShakeDistance;

	//True if can shake, false otherwise.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shake")
	bool bCanShake;

	//True if it is shaking, false otherwise.
	bool bIsShaking;

	//Time beetween start and end shake.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shake")
	float IntervalTime;

	//ShakingDirection
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shake")
	bool bLeft;
	
	FTimerHandle ShakeTimer;

	//Store the initial position to move the mesh in the initial position after shaking.
	FVector StartPosition;
	

	//Shake and wait shake used with the timer to change from shaking to not shaking.
	virtual void Shake();

	virtual void WaitShake();

	//Used to currently move the actor
	virtual void ShakingActor(float);


#pragma endregion

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
