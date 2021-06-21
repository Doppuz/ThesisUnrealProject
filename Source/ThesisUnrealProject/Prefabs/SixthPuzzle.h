// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Character/PawnInteractiveClass.h"
#include "SixthPuzzle.generated.h"

class AAICharacterPawnQuad;

UCLASS()
class THESISUNREALPROJECT_API ASixthPuzzle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASixthPuzzle();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* Doors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UChildActorComponent* Door1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UChildActorComponent* Door2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UChildActorComponent* Door3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* PuzzleButtons;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UChildActorComponent* Puzzle1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* FallenPlatforms;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UChildActorComponent* FallenPlatform1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* Triggers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UBoxComponent* Trigger1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UBoxComponent* Trigger2;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UFUNCTION()
	void OnOverlapStart(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit);

	UFUNCTION()
	void PuzzleOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit);

	UFUNCTION()
	void FallenEvent();
};
