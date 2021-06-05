// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorSpawnerWithOwner.h"
#include "../Character/EnemyAIAbstract.h"

// Sets default values
AActorSpawnerWithOwner::AActorSpawnerWithOwner(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bDestroyAfterSpawn = false;
}

AActor* AActorSpawnerWithOwner::SpawnActor() {
	AEnemyAIAbstract* NewActor = Cast<AEnemyAIAbstract>(GetWorld()->SpawnActor<AActor>(ActorToSpawn,GetActorLocation(),GetActorRotation()));

	if(RiddleActor != nullptr)
		RiddleActor->EnemyActivator.Add(NewActor);
	else
		UE_LOG(LogTemp,Warning,TEXT("No RiddleActor set"));

	return NewActor;

}

// Called when the game starts or when spawned
void AActorSpawnerWithOwner::BeginPlay(){

	Super::BeginPlay();

}
