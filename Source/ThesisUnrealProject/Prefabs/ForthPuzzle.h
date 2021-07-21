// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ForthPuzzle.generated.h"

class APuzzleButton;

UCLASS()
class THESISUNREALPROJECT_API AForthPuzzle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AForthPuzzle();

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
	UChildActorComponent* NPC3;

	UPROPERTY(EditAnywhere, Category = "Components")
	UChildActorComponent* NPC4;

	UPROPERTY(EditAnywhere, Category = "Components")
	USceneComponent* PuzzleButtons;

	UPROPERTY(EditAnywhere, Category = "Components")
	UChildActorComponent* Puzzle1;

	UPROPERTY(EditAnywhere, Category = "Components")
	UChildActorComponent* Puzzle2;

	UPROPERTY(EditAnywhere, Category = "Components")
	UChildActorComponent* Puzzle3;
	
	UPROPERTY(EditAnywhere, Category = "Components")
	UChildActorComponent* Puzzle4;

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

// --- Allies ---

	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit);

	int PuzzleCount;
};
