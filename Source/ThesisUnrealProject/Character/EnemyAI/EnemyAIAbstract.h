// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EnemyAIAbstract.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEndDelegate,AEnemyAIAbstract*, Enemy);

UCLASS(Abstract)
class THESISUNREALPROJECT_API AEnemyAIAbstract : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemyAIAbstract();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	float MaxHealth;

	UPROPERTY(VisibleAnywhere)
	float CurrentHealth;

	//Check if I am destroyed
	bool bIAmDestroyed;

	// End delegate
	FEndDelegate End;


};
