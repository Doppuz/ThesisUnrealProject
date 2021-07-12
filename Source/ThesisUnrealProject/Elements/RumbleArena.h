// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorSpawner.h"
#include "../Character/EnemyAIAbstract.h"
#include "RumbleArena.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEndArena);

class ACoinController;

UCLASS()
class THESISUNREALPROJECT_API ARumbleArena : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARumbleArena();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

#pragma region Components
	
	//UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	//USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	class UBoxComponent* Collider;

	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;
	
	UPROPERTY(EditAnywhere,Category = "Spawn")
	TSubclassOf<AActorSpawner> SpawnerClass;

	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	USceneComponent* FirstSpawnPosition;
	
	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	USceneComponent* SecondSpawnPosition;
	
	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	USceneComponent* ThirdSpawnPosition;
	
	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	USceneComponent* FourthSpawnPosition;

	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	USceneComponent* RewardSpawnPosition;

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
	FEndArena EndArena;

private:

	bool CheckAllEnemyDeath();

};
