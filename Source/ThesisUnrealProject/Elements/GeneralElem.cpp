// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneralElem.h"
#include "CoinController.h"

// Sets default values
AGeneralElem::AGeneralElem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Root->SetRelativeScale3D(FVector(9.f,9.f,9.f));

	SpawnCoinPosition = CreateDefaultSubobject<USceneComponent>(TEXT("CoinSpawnPosition"));
	SpawnCoinPosition->SetupAttachment(RootComponent);

	MeshComponent1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh 1"));
	MeshComponent1->SetupAttachment(RootComponent);

	MeshComponent1->SetRelativeLocation(FVector(-20,0,0));

	MeshComponent2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh 2"));
	MeshComponent2->SetupAttachment(RootComponent);
	
	MeshComponent2->SetRelativeLocation(FVector(60,0,0));

	MeshComponent3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh 3"));
	MeshComponent3->SetupAttachment(RootComponent);

	MeshComponent3->SetRelativeLocation(FVector(-60,0,0));

	ItHasCoin = false;
}

// Called when the game starts or when spawned
void AGeneralElem::BeginPlay()
{
	Super::BeginPlay();

	int RandomNumber = FMath::RandRange(0,Meshes.Num() + 1);
	if(RandomNumber < Meshes.Num())
		MeshComponent1->SetStaticMesh(Meshes[RandomNumber]);

	RandomNumber = FMath::RandRange(0,Meshes.Num() + 1);
	if(RandomNumber < Meshes.Num())
		MeshComponent2->SetStaticMesh(Meshes[RandomNumber]);
	
	RandomNumber = FMath::RandRange(0,Meshes.Num() + 1);
	if(RandomNumber < Meshes.Num())
		MeshComponent3->SetStaticMesh(Meshes[RandomNumber]);
}

