// Fill out your copyright notice in the Description page of Project Settings.


#include "RiddleTemplate.h"

// Sets default values
ARiddleTemplate::ARiddleTemplate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bSolved = false;
	bUseTurnMethodology = false;
}

// Called when the game starts or when spawned
void ARiddleTemplate::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARiddleTemplate::CheckPuzzleActor() {
	
}

void ARiddleTemplate::CheckAllyActor() {
	
}

void ARiddleTemplate::CheckEnemyActor() {
	
}

// Called every frame
void ARiddleTemplate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

