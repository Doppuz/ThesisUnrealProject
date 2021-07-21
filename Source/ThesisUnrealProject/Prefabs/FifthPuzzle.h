// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FifthPuzzle.generated.h"

class APuzzleButton;

UCLASS()
class THESISUNREALPROJECT_API AFifthPuzzle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFifthPuzzle();

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
	USceneComponent* UI;

	//OverlayedText
	UPROPERTY( VisibleAnywhere,Category = "Components")
	class UWidgetComponent* OverlayedTextCoins;

	UPROPERTY( VisibleAnywhere,Category = "Components" )
	class UWidgetComponent* OverlayedTextWall;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

// --- Gates ---
	UFUNCTION()
	void Destruction(ADestructibleElements* Elem);

	int GatesDestructed;

// --- Coins ---

	UFUNCTION()
	void CoinCollected();

	int CoinsCollected;
};
