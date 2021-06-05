// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorSpawner.generated.h"

UCLASS()
class THESISUNREALPROJECT_API AActorSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActorSpawner();

	UPROPERTY(EditAnywhere, Category = "ActorSpawn")
	TSubclassOf<AActor> ActorToSpawn;

	UPROPERTY(EditAnywhere, Category = "ActorSpawn")
	bool bDestroyAfterSpawn;

	//SpawnActorMethos
	virtual AActor* SpawnActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;




};
