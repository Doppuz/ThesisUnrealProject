// Fill out your copyright notice in the Description page of Project Settings.


#include "Crate.h"
#include "Components/BoxComponent.h"
#include "DestructibleComponent.h"

// Sets default values
ACrate::ACrate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxCollider->SetupAttachment(RootComponent);

	CrateMesh = CreateDefaultSubobject<UDestructibleComponent>(TEXT("Crate Mesh DM"));
	CrateMesh->SetupAttachment(BoxCollider);

}

// Called when the game starts or when spawned
void ACrate::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACrate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

