// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorSpawner.h"
#include "RiddleTemplate.h"
#include "ActorSpawnerWithOwner.generated.h"

UCLASS()
class THESISUNREALPROJECT_API AActorSpawnerWithOwner : public AActorSpawner
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActorSpawnerWithOwner();

	UPROPERTY(EditAnywhere, Category = "SpawnActor")
	TArray<TSubclassOf<AActor>> ActorsToSpawn;
	
	//Used if I need to link the spawned actors with a Riddle object.
	UPROPERTY(EditAnywhere, Category = "SpawnActor")
	ARiddleTemplate* RiddleActor;

	//SpawnActorMethos
	virtual void SpawnActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;




};
