// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnInteractiveClass.h"

// Sets default values
APawnInteractiveClass::APawnInteractiveClass()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APawnInteractiveClass::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APawnInteractiveClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APawnInteractiveClass::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APawnInteractiveClass::StartInteraction() {
	
}

void APawnInteractiveClass::EndInteraction() {
	
}

