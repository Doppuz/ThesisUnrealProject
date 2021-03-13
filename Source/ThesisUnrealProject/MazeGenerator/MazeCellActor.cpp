// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeCellActor.h"

// Sets default values
AMazeCellActor::AMazeCellActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	MeshComponent->SetupAttachment(RootComponent);

}

void AMazeCellActor::Init(UStaticMesh* MeshPar) {
	Mesh = MeshPar;
	MeshComponent->SetStaticMesh(Mesh);
}

// Called when the game starts or when spawned
void AMazeCellActor::BeginPlay()
{
	Super::BeginPlay();
	
}


