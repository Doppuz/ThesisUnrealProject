// Fill out your copyright notice in the Description page of Project Settings.


#include "CrateElements.h"
#include "Components/BoxComponent.h"
#include "DestructibleComponent.h"
#include "CoinController.h"

// Sets default values
ACrateElements::ACrateElements()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	SpawnCoinPosition = CreateDefaultSubobject<USceneComponent>(TEXT("CoinSpawnPosition"));
	SpawnCoinPosition->SetupAttachment(RootComponent);

	DestructibleComponent = CreateDefaultSubobject<UDestructibleComponent>(TEXT("Crate Mesh DM"));
	DestructibleComponent->SetupAttachment(RootComponent);

	MeshComponent1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh 1"));
	MeshComponent1->SetupAttachment(RootComponent);

	MeshComponent2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh 2"));
	MeshComponent2->SetupAttachment(RootComponent);

	MeshComponent3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh 3"));
	MeshComponent3->SetupAttachment(RootComponent);

	IAmDestructed = false;
	ItHasCoin = false;

}

// Called when the game starts or when spawned
void ACrateElements::BeginPlay(){
	Super::BeginPlay();
	DestructibleComponent->OnComponentFracture.AddDynamic(this,&ACrateElements::OnComponentFracture);

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

// Called every frame
void ACrateElements::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
}

void ACrateElements::OnComponentFracture(const FVector& HitPoint, const FVector& HitDirection) {
	if(!IAmDestructed){

		FVector Position = SpawnCoinPosition->GetComponentLocation();
    	
		FRotator Rotation = FRotator(0,0,0);
		
		AActor* Coin = GetWorld()->SpawnActor<ACoinController>(CoinClass,Position,Rotation);
		
		if(Coin != nullptr){
    		Coin->SetFolderPath(TEXT("Coins"));
		}else
			UE_LOG(LogTemp,Warning,TEXT("nullptr"));
	}
	IAmDestructed = true;
}


