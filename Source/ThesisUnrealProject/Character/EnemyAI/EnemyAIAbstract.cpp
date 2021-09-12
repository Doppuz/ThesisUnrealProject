// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIAbstract.h"

// Sets default values
AEnemyAIAbstract::AEnemyAIAbstract()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bIAmDestroyed = false;
	bSpawnCoin = false;

}

// Called when the game starts or when spawned
void AEnemyAIAbstract::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AEnemyAIAbstract::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyAIAbstract::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) 
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
