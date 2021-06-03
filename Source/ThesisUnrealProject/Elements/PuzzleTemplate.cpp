// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleTemplate.h"

// Sets default values
APuzzleTemplate::APuzzleTemplate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bSolved = false;
}

// Called when the game starts or when spawned
void APuzzleTemplate::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APuzzleTemplate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

