// Fill out your copyright notice in the Description page of Project Settings.


#include "CrateElements.h"
#include "Components/BoxComponent.h"
#include "DestructibleComponent.h"
#include "CoinController.h"
#include "RiddleTemplate.h"

// Sets default values
ACrateElements::ACrateElements()
{
	PrimaryActorTick.bCanEverTick = false;

	DestructibleComponent = CreateDefaultSubobject<UDestructibleComponent>(TEXT("Crate Mesh DM"));
	DestructibleComponent->SetupAttachment(RootComponent);

	DestructibleComponent->SetRelativeLocation(FVector(20,16,-10));

	IAmDestructed = false;
}

// Called when the game starts or when spawned
void ACrateElements::BeginPlay(){
	Super::BeginPlay();
	DestructibleComponent->OnComponentFracture.AddDynamic(this,&ACrateElements::OnComponentFracture);

}

void ACrateElements::OnComponentFracture(const FVector& HitPoint, const FVector& HitDirection) {
	if(!IAmDestructed){

		FVector Position = SpawnCoinPosition->GetComponentLocation();
    	
		FRotator Rotation = FRotator(0,0,0);
		
		ACoinController* Coin = GetWorld()->SpawnActor<ACoinController>(CoinClass,Position,Rotation);

		if(CollectorActor != nullptr)
			CollectorActor->CoinActivator.Add(Coin);
		
		if(Coin != nullptr){
    		Coin->SetFolderPath(TEXT("Coins"));
		}else
			UE_LOG(LogTemp,Warning,TEXT("nullptr"));
	}
	IAmDestructed = true;
}


