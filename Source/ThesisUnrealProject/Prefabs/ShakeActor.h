// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShakeActor.generated.h"

class APuzzleButton;

UCLASS()
class THESISUNREALPROJECT_API AShakeActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShakeActor();

	UPROPERTY(EditAnywhere, Category = "Components")
	USceneComponent* Root;

	UPROPERTY(EditAnywhere, Category = "Components")
	UChildActorComponent* ShakingActor;

	UPROPERTY(Editanywhere, Category = "Components")
	class UBoxComponent* LeftTrigger;
	
	UPROPERTY(Editanywhere, Category = "Components")
	class UBoxComponent* RightTrigger;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

#pragma region Shake

	//Shake speed.
	UPROPERTY(EditAnywhere, Category = "Shake")
	float ShakeSpeed;

	//True if it is shaking, false otherwise.
	bool bIsShaking;

	//Time beetween start and end shake.
	UPROPERTY(EditAnywhere, Category = "Shake")
	float IntervalTime;

	UPROPERTY(EditAnywhere, Category = Shake)
	bool ShakeLeft;
	
	FTimerHandle ShakeTimer;

	//Store the initial position to move the mesh in the initial position after shaking.
	FVector StartPosition;
	

	//Shake and wait shake used with the timer to change from shaking to not shaking.
	virtual void EnableShake();

	virtual void WaitShake();

	//Used to currently move the actor
	virtual void Shake(float);


#pragma endregion

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit);


};
