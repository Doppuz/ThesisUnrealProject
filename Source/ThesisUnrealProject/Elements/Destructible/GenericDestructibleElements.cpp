// Fill out your copyright notice in the Description page of Project Settings.


#include "GenericDestructibleElements.h"
#include "DestructibleComponent.h"
#include "../../GameModeTutorial.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../GeneralElements/CoinController.h"

int AGenericDestructibleElements::IDCounter = 0;

// Sets default values
AGenericDestructibleElements::AGenericDestructibleElements(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	DestructibleMesh = CreateDefaultSubobject<UDestructibleComponent>(TEXT("DestructibleMesh"));
	DestructibleMesh->SetupAttachment(RootComponent);

	bIAmDestroyed = false;

	CoinOffset = FVector(0.f, 0.f, 20.f);

	ForceApplied = 1000.f;

}

// Called when the game starts or when spawned
void AGenericDestructibleElements::BeginPlay(){
	Super::BeginPlay();

	ID = IDCounter;
	IDCounter = (IDCounter + 1) % 50000;

	DestructibleMesh->OnComponentFracture.AddDynamic(this,&AGenericDestructibleElements::OnComponentFracture);
	
	UGameplayStatics::GetPlayerPawn(GetWorld(),0)->MoveIgnoreActorAdd(this);

	if(SpawnActor != nullptr && SpawnActor.Get()->IsChildOf( ACoinController::StaticClass())){
	
		AGameModeAbstract* GameMode = Cast<AGameModeAbstract>(GetWorld()->GetAuthGameMode());
		GameMode->TotalCoins += 1;
	
	}

}

void AGenericDestructibleElements::OnComponentFracture(const FVector& HitPoint, const FVector& HitDirection) {
	AGameModeTutorial* GameMode = Cast<AGameModeTutorial>(GetWorld()->GetAuthGameMode());

	if(!bIAmDestroyed){
		bIAmDestroyed = true;
		if (SpawnActor != nullptr) {
		
			if(SpawnActor != nullptr && SpawnActor.Get()->IsChildOf( ACoinController::StaticClass())){

				FTransform Transform;
				Transform.SetLocation(GetActorLocation() + CoinOffset);
				ACoinController* Coin = Cast<ACoinController>(GetWorld()->SpawnActorDeferred<ACoinController>(SpawnActor, Transform));
				Coin->bNoIncrease = true;
				Coin->FinishSpawning(Transform);
				Coin->bNoIncrease = false;
				DestrDelegate.Broadcast(Coin);

			}else{

				AActor* Actor = GetWorld()->SpawnActor<AActor>(SpawnActor, GetActorLocation() + CoinOffset, GetActorRotation());
				DestrDelegate.Broadcast(Actor);
			
			}
		
		}else
			DestrDelegate.Broadcast(nullptr);

	}

}
