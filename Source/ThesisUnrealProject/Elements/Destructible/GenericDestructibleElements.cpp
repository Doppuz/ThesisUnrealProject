// Fill out your copyright notice in the Description page of Project Settings.


#include "GenericDestructibleElements.h"
#include "DestructibleComponent.h"
#include "../../GameModeTutorial.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

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

}

// Called when the game starts or when spawned
void AGenericDestructibleElements::BeginPlay(){
	Super::BeginPlay();

	ID = IDCounter;
	IDCounter = (IDCounter + 1) % 50000;

	DestructibleMesh->OnComponentFracture.AddDynamic(this,&AGenericDestructibleElements::OnComponentFracture);
	
	UGameplayStatics::GetPlayerPawn(GetWorld(),0)->MoveIgnoreActorAdd(this);

}

void AGenericDestructibleElements::OnComponentFracture(const FVector& HitPoint, const FVector& HitDirection) {
	AGameModeTutorial* GameMode = Cast<AGameModeTutorial>(GetWorld()->GetAuthGameMode());

	if(!bIAmDestroyed){
		bIAmDestroyed = true;
		if (SpawnActor != nullptr) {
			AActor* Actor = GetWorld()->SpawnActor<AActor>(SpawnActor, GetActorLocation() + FVector(0.f, 0.f, 20.f), GetActorRotation());
			DestrDelegate.Broadcast(Actor);
		}else
			DestrDelegate.Broadcast(nullptr);

	}

}
