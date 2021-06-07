// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RiddleTemplate.h"
#include "DestructibleElements.generated.h"

UCLASS()
class THESISUNREALPROJECT_API ADestructibleElements : public ARiddleTemplate
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADestructibleElements();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Destruction")
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Destruction")
	class UBoxComponent* Collider;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Destruction")
	class UDestructibleComponent* DestructibleMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General")
	int ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Destroy")
	float Health;

	float CurrentDamage;

	bool bIAmDestroyed;

	void HitMesh(const FHitResult& Hit);

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

	FTimerHandle ShakeTimer;

	//Store the initial position to move the mesh in the initial position after shaking.
	FVector StartPosition;
	
	void Shake();

	void WaitShake();

#pragma endregion

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UFUNCTION()
	void OnComponentFracture(const FVector& HitPoint, const FVector& HitDirection);

};
