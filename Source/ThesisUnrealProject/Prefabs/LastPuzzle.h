// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LastPuzzle.generated.h"

class APuzzleButton;
class ACoinController;

UCLASS()
class THESISUNREALPROJECT_API ALastPuzzle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALastPuzzle();

	UPROPERTY(EditAnywhere, Category = "Components")
	USceneComponent* Root;

	UPROPERTY(EditAnywhere, Category = "Components")
	USceneComponent* Doors;

	UPROPERTY(EditAnywhere, Category = "Components")
	UChildActorComponent* Door1;

	UPROPERTY(EditAnywhere, Category = "Components")
	USceneComponent* NPCs;

	UPROPERTY(EditAnywhere, Category = "Components")
	UChildActorComponent* NPC1;

	UPROPERTY(EditAnywhere, Category = "Components")
	UChildActorComponent* NPC2;

	UPROPERTY(EditAnywhere, Category = "Components")
	USceneComponent* DestructibleGate;

	UPROPERTY(EditAnywhere, Category = "Components")
	UChildActorComponent* DestrGate1;
	
	UPROPERTY(EditAnywhere, Category = "Components")
	UChildActorComponent* DestrGate2;

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

// --- Allies ---

	UFUNCTION()
	void SpokenAlliesEvent(APawnInteractiveClass* SpokenActor);

	int SpokenAllies;

// --- Destruction ---
	
	UFUNCTION()
	void Destruction(ADestructibleElements* Elem);

// --- Coins ---

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAcces = true), Category = "Destruction")
	TSubclassOf<ACoinController> CoinClass;

	UFUNCTION()
	void CoinCollected();

	int CoinsCollected;
};
