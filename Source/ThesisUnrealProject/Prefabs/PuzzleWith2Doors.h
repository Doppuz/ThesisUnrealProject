// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleWith2Doors.generated.h"

class APuzzleButton;
class ADestructibleElements;

UCLASS()
class THESISUNREALPROJECT_API APuzzleWith2Doors : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuzzleWith2Doors();

	UPROPERTY(EditAnywhere, Category = "Components")
	USceneComponent* Root;

	UPROPERTY(EditAnywhere, Category = "Components")
	USceneComponent* Doors;

	UPROPERTY(EditAnywhere, Category = "Components")
	UChildActorComponent* Door1;

	UPROPERTY(EditAnywhere, Category = "Components")
	UChildActorComponent* Door2;

	UPROPERTY(EditAnywhere, Category = "Components")
	USceneComponent* PuzzleButtons;

	UPROPERTY(EditAnywhere, Category = "Components")
	UChildActorComponent* Puzzle1;

	UPROPERTY(EditAnywhere, Category = "Components")
	UChildActorComponent* Puzzle2;

	UPROPERTY(EditAnywhere, Category = "Components")
	UChildActorComponent* Puzzle3;

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
	class UWidgetComponent* OverlayedTextGate;

	UPROPERTY( VisibleAnywhere,Category = "Components" )
	class UWidgetComponent* OverlayedTextPuzzle;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditAnywhere, Category = "Order")
	TArray<APuzzleButton*> RightOrder;

	UPROPERTY(VisibleAnywhere, Category = "Order")
	TArray<APuzzleButton*> MyOrder;

	FTimerHandle ResetPuzzleTimer;

// ------- Materials ---------
	
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = "true"), Category = Materials)
	UMaterial* GreenColor;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = "true"), Category = Materials)
	UMaterial* RedColor;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = "true"), Category = Materials)
	UMaterial* GreyColor;

// ----------------------------

	//Check if the order is right.
	void CheckPuzzleActor();

	//Reset the color of the puzzle.
	void ResetPuzzle();
	
	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit);

// --- Destruction ---
	UFUNCTION()
	void DestructionEvent(ADestructibleElements* Elem);
};
