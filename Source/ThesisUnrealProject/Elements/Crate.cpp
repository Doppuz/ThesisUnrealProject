// Fill out your copyright notice in the Description page of Project Settings.


#include "Crate.h"
#include "Components/BoxComponent.h"
#include "DestructibleComponent.h"
#include "CoinController.h"

// Sets default values
ACrate::ACrate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	DestructibleComponent = CreateDefaultSubobject<UDestructibleComponent>(TEXT("Crate Mesh DM"));
	DestructibleComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ACrate::BeginPlay(){
	Super::BeginPlay();
	DestructibleComponent->OnComponentFracture.AddDynamic(this,&ACrate::OnComponentFracture);
}

// Called every frame
void ACrate::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
}

void ACrate::OnComponentFracture(const FVector& HitPoint, const FVector& HitDirection) {
	if(!IAmDestructed){
		FVector Position = FVector(GetActorLocation().X,
            GetActorLocation().Y, 300.f);
    	FRotator Rotation = FRotator(0,0,0);
    	AActor* Coin = GetWorld()->SpawnActor<ACoinController>(CoinClass,Position,Rotation);
    	Coin->SetFolderPath(TEXT("Coins"));
	}
	IAmDestructed = true;
}


