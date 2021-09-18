// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Room.h"
#include "../Spawner/ActorSpawner.h"
#include "../../Character/EnemyAI/EnemyAIAbstract.h"
#include "RoomKiller.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEndArenaDelegate);

class APawnInteractiveClass;

UCLASS()
class THESISUNREALPROJECT_API ARoomKiller : public ARoom
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoomKiller();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

#pragma region Components

	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	USceneComponent* SpawnPositions;

	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	USceneComponent* FirstSpawnPosition;
	
	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	USceneComponent* SecondSpawnPosition;
	
	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	USceneComponent* ThirdSpawnPosition;
	
	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	USceneComponent* FourthSpawnPosition;

	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	USceneComponent* PortalSpawnPosition;
	
	UPROPERTY(EditAnywhere,Category = "Spawn")
	TSubclassOf<AActorSpawner> SpawnerClass;

#pragma endregion

	UPROPERTY(EditAnywhere)
	int TurnNumbers;

	TArray<AActorSpawner*> Spawners;

	TArray<AEnemyAIAbstract*> Enemies;

	UPROPERTY(EditAnywhere, Category = "SpawnActor")
	TArray<TSubclassOf<AEnemyAIAbstract>> ActorsToSpawn;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Reward)
	TSubclassOf<ACoinController> RewardClass;

	//Delegate for the end of the arena.
	FEndArenaDelegate EndArena;

	UPROPERTY(EditAnywhere, Category = "Elements")
	TSubclassOf<APawnInteractiveClass> NpcClass;

	APawnInteractiveClass* InteractiveActor;

	UFUNCTION()
	void Start();

	UFUNCTION()
	void ReStartNpc(APawnInteractiveClass* SpokenActor);

	bool bStart = false;

private:

	bool CheckAllEnemyDeath();



};
