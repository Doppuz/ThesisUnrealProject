// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NPC4Doors.generated.h"

class APuzzleButton;

UCLASS()
class THESISUNREALPROJECT_API ANPC4Doors : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANPC4Doors();

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
	USceneComponent* NPCs;

	UPROPERTY(EditAnywhere, Category = "Components")
	UChildActorComponent* NPC1;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UFUNCTION()
	void LeftChoiceEvent();
	
	UFUNCTION()
	void RightChoiceEvent();

};
