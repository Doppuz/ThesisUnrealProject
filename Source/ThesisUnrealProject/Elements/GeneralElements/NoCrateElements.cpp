// Fill out your copyright notice in the Description page of Project Settings.


#include "NoCrateElements.h"

// Sets default values
ANoCrateElements::ANoCrateElements()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh 4"));
	MeshComponent4->SetupAttachment(RootComponent);

	MeshComponent4->SetRelativeLocation(FVector(20,0,0));

}

// Called when the game starts or when spawned
void ANoCrateElements::BeginPlay()
{
	Super::BeginPlay();
	
	int RandomNumber = FMath::RandRange(0,Meshes.Num() + 1);
	if(RandomNumber < Meshes.Num())
		MeshComponent4->SetStaticMesh(Meshes[RandomNumber]);
}


