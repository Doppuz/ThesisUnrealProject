// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SecondPuzzle.generated.h"

class APuzzleButton;

UCLASS()
class THESISUNREALPROJECT_API ASecondPuzzle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASecondPuzzle();

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
	UChildActorComponent* Door4;

	UPROPERTY(EditAnywhere, Category = "Components")
	UChildActorComponent* Door5;

	UPROPERTY(EditAnywhere, Category = "Components")
	USceneComponent* Enemies;

	UPROPERTY(EditAnywhere, Category = "Components")
	UChildActorComponent* Enemy1;

	UPROPERTY(EditAnywhere, Category = "Components")
	UChildActorComponent* Enemy2;

	UPROPERTY(EditAnywhere, Category = "Components")
	UChildActorComponent* Enemy3;

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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	//Check if the order is right.
	void CheckPuzzleActor();

	UFUNCTION()
	void LeftChoiceEvent();
	
	UFUNCTION()
	void RightChoiceEvent();

// ---- Enemies ----

	UFUNCTION()
	void EndEnemiesEvent();

	int DeathEnemies;

// --- Allies ---

	UFUNCTION()
	void SpokenAlliesEvent();

	int SpokenAllies;

};
