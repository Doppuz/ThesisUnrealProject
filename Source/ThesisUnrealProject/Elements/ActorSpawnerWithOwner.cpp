// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorSpawnerWithOwner.h"

// Sets default values
AActorSpawnerWithOwner::AActorSpawnerWithOwner(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bDestroyAfterSpawn = false;
}

void AActorSpawnerWithOwner::SpawnActor() {
	AActor* NewActor = GetWorld()->SpawnActor<AActor>(ActorToSpawn,GetActorLocation(),GetActorRotation());

	RiddleActor->EnemyActivator.Add(NewActor);

	if(bDestroyAfterSpawn)
		Destroy();
}

// Called when the game starts or when spawned
void AActorSpawnerWithOwner::BeginPlay(){

	Super::BeginPlay();

}
