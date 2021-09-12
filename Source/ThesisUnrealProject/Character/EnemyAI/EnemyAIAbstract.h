// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EnemyAIAbstract.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEndDelegate,AEnemyAIAbstract*, Enemy);

class ACoinController;

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

	//Tick it if you want to spawn a coin after the death of the Enemy.
	UPROPERTY(EditAnywhere, Category = "Spawn")
	bool bSpawnCoin;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<ACoinController> SpawnCoin;

	// End delegate
	FEndDelegate End;


};
