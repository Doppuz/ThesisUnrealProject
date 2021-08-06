// Fill out your copyright notice in the Description page of Project Settings.


#include "ChestController.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AChestController::AChestController(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	ChestCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("ChestCollider"));
	ChestCollider->SetupAttachment(RootComponent);

	ChestMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ChestMesh"));
	ChestMesh->SetupAttachment(ChestCollider);
}

// Called when the game starts or when spawned
void AChestController::BeginPlay(){
	Super::BeginPlay();
	
}

// Called every frame
void AChestController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

