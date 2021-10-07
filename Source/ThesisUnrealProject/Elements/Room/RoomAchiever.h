// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Room.h"
#include "RoomAchiever.generated.h"

class ACoinController;
class ADoor;
class AAIShooterPawn;

UCLASS()
class THESISUNREALPROJECT_API ARoomAchiever : public ARoom{

	GENERATED_BODY()
	
public:

	ARoomAchiever();

	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	USceneComponent* SpawnPositions;

	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	USceneComponent* StartSpawnPosition;
	
	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	USceneComponent* MiddleSpawnPosition;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ACoinController> CoinClass;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> MetalCrateClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AAIShooterPawn> ShooterPawnClass;


	int CoinsCollected;

	int TotalCoins;

	FVector EndPos;

	ADoor* Door;

	TArray<AAIShooterPawn*> Shooters;

	UFUNCTION()
	void OnCoinCollect();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
