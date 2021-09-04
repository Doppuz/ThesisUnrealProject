// Fill out your copyright notice in the Description page of Project Settings.


#include "Stair.h"

// Sets default values
AStair::AStair()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Instance = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Root"));
    RootComponent = Instance;
	Instance->ComponentTags.Add("ResetJump");

	StepsNumber = 8;
	StepsDistance = 700.f;
	InitialOffset = 375.f;
	StepsHeightDistance = -100.f;

}

// Called when the game starts or when spawned
void AStair::BeginPlay()
{
	Super::BeginPlay();
	
	for(int i = 0; i < StepsNumber; i++){
		
		FTransform Transform;
		FVector SpawnLocation(InitialOffset + StepsDistance * i,0.f,0.f + StepsHeightDistance * i);
		Transform.SetLocation(SpawnLocation);
		Instance->AddInstance(Transform);

	}

	/*for(int i = 0; i < 13; i++){

		for(int j = 0; j < 13; j++){
		
			FTransform Transform;
			FVector SpawnLocation(0.f + 1100.f * i,0.f + 1100.f * j,0.f);
			Transform.SetLocation(SpawnLocation);
			Instance->AddInstance(Transform);

		}

	}*/

}

// Called every frame
void AStair::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

