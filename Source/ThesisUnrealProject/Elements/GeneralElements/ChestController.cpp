// Fill out your copyright notice in the Description page of Project Settings.


#include "ChestController.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AChestController::AChestController(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	ChestCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("ChestCollider"));
	ChestCollider->SetupAttachment(RootComponent);

	ChestMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ChestMesh"));
	ChestMesh->SetupAttachment(ChestCollider);
}
