// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Door.h"
#include "../../Spawner/ActorSpawner.h"
#include "../../../Character/EnemyAI/EnemyAIAbstract.h"
#include "DoorKiller.generated.h"

/**
 * 
 */
UCLASS()
class THESISUNREALPROJECT_API ADoorKiller : public ADoor{

	GENERATED_BODY()

public:

	ADoorKiller();

	UPROPERTY(VisibleAnywhere)
	USceneComponent* SpawnPos1;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* SpawnPos2;

	UPROPERTY(EditAnywhere,Category = "Spawn")
	TSubclassOf<AActorSpawner> SpawnerClass;

	UPROPERTY(EditAnywhere)
	int TurnNumbers;

	//Store the two spawners
	TArray<AActorSpawner*> Spawners;

	//Store the enemies for each round to  be eliminated
	TArray<AEnemyAIAbstract*> Enemies;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	TArray<TSubclassOf<AEnemyAIAbstract>> ActorsToSpawn;

	virtual void Tick(float DeltaTime) override;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:

	bool CheckAllEnemyDeath();
};
