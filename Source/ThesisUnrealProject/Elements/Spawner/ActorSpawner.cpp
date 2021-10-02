// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorSpawner.h"

// Sets default values
AActorSpawner::AActorSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	bDestroyAfterSpawn = true;
}

AActor* AActorSpawner::SpawnActor() {
	AActor* Actor = GetWorld()->SpawnActor<AActor>(ActorToSpawn,GetActorLocation(),GetActorRotation());;
	return Actor;
}

// Called when the game starts or when spawned
void AActorSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	if(bDestroyAfterSpawn){
		SpawnActor();
		Destroy();
	}
}
