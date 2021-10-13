// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorInstanceMesh.h"

// Sets default values
AFloorInstanceMesh::AFloorInstanceMesh()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;

	FloorInstances = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("FloorInstances"));
    FloorInstances->SetupAttachment(RootComponent);

	FTransform Transform;
	NumberOfCells = 50;

	for(int i = 0; i < NumberOfCells; i++){

		for(int j = 0; j < NumberOfCells; j++){
		
			Transform.SetLocation(FVector(-768.f * i,-768.f * j,0.f));
			FloorInstances->AddInstance(Transform);

		}

	}

}

// Called when the game starts or when spawned
void AFloorInstanceMesh::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFloorInstanceMesh::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

