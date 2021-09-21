// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShakeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THESISUNREALPROJECT_API UShakeComponent : public UActorComponent{

	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UShakeComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

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

	FRotator StartRotator;

	float InitialRot;

	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

private:

	AActor* Parent;

};
