// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ThirdPuzzle.generated.h"

class APuzzleButton;

UCLASS()
class THESISUNREALPROJECT_API AThirdPuzzle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AThirdPuzzle();

	UPROPERTY(EditAnywhere, Category = "Components")
	USceneComponent* Root;

	UPROPERTY(EditAnywhere, Category = "Components")
	USceneComponent* Doors;

	UPROPERTY(EditAnywhere, Category = "Components")
	UChildActorComponent* Door1;

	UPROPERTY(EditAnywhere, Category = "Components")
	UChildActorComponent* Door2;

	UPROPERTY(EditAnywhere, Category = "Components")
	UChildActorComponent* Door3;

	UPROPERTY(EditAnywhere, Category = "Components")
	USceneComponent* DestructibleGate;

	UPROPERTY(EditAnywhere, Category = "Components")
	UChildActorComponent* DestrGate1;

	UPROPERTY(EditAnywhere, Category = "Components")
	UChildActorComponent* DestrGate2;

	UPROPERTY(EditAnywhere, Category = "Components")
	UChildActorComponent* DestrGate3;

	UPROPERTY(EditAnywhere, Category = "Components")
	UChildActorComponent* DestrGate4;

	UPROPERTY(EditAnywhere, Category = "Components")
	UChildActorComponent* DestrGate5;

	//UPROPERTY(EditAnywhere, Category = "Components")
	//UChildActorComponent* DestrGate6;

	UPROPERTY(EditAnywhere, Category = "Components")
	USceneComponent* Coins;

	UPROPERTY(EditAnywhere, Category = "Components")
	UChildActorComponent* Coin1;

	UPROPERTY(EditAnywhere, Category = "Components")
	UChildActorComponent* Coin2;

	UPROPERTY(EditAnywhere, Category = "Components")
	UChildActorComponent* Coin3;

	UPROPERTY(EditAnywhere, Category = "Components")
	UChildActorComponent* Coin4;

	UPROPERTY(EditAnywhere, Category = "Components")
	UChildActorComponent* Coin5;

	UPROPERTY(EditAnywhere, Category = "Components")
	UChildActorComponent* Coin6;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

// --- Gates ---
	UFUNCTION()
	void Destruction();

	int GatesDestructed;

// --- Coins ---

	UFUNCTION()
	void OnCoinOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit);

	int CoinsCollected;
};
