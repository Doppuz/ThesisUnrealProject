// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../GeneralRoomWithDoor.h"
#include "ArenaEnemies.generated.h"

class ACoinController;
class AEnemyAIAbstract;
class ADoor;

/**
 * 
 */
UCLASS()
class THESISUNREALPROJECT_API AArenaEnemies : public AGeneralRoomWithDoor
{
	GENERATED_BODY()
	
public:

	AArenaEnemies();

	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	USceneComponent* SpawnPositions;

	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	USceneComponent* Spawn1;

	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	USceneComponent* Spawn2;
	
	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	USceneComponent* Spawn3;
	
	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	USceneComponent* Spawn4;
	
	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	USceneComponent* Spawn5;
	
	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	USceneComponent* Spawn6;
	
	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	USceneComponent* Spawn7;
	
	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	USceneComponent* Spawn8;
	
	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	USceneComponent* Spawn9;

// ----- Classes -----

	UPROPERTY(EditAnywhere, Category = "SpawnElements")
	TSubclassOf<ACoinController> CoinClass;
	
	UPROPERTY(EditAnywhere, Category = "SpawnElements")
	TArray<TSubclassOf<AEnemyAIAbstract>> EnemiesClass;

	UPROPERTY(EditAnywhere, Category = "SpawnElements")
	int EnemiesNumber;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	void SpawnEnemies();

	UFUNCTION()
	void SpawnCoins(AEnemyAIAbstract* Enemy);

	virtual void OpenDoor();

	int CoinsCollected;
	

};
