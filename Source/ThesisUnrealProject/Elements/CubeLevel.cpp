// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeLevel.h"
#include "Components/BoxComponent.h"

// Sets default values
ACubeLevel::ACubeLevel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	RootComponent = Collider;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collider);

}

// Called when the game starts or when spawned
void ACubeLevel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACubeLevel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

