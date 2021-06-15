// Fill out your copyright notice in the Description page of Project Settings.


#include "DestructibleElements.h"
#include "DestructibleComponent.h"
#include "../GameModeTutorial.h"
#include "Components/BoxComponent.h"
#include "Door.h"

// Sets default values
ADestructibleElements::ADestructibleElements(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Collider->SetupAttachment(RootComponent);

	DestructibleMesh = CreateDefaultSubobject<UDestructibleComponent>(TEXT("DestructibleMesh"));
	DestructibleMesh->SetupAttachment(Collider);

	DestructibleMesh->SetSimulatePhysics(false);

	Health = 1.f;
	bIAmDestroyed = false;
	ID = -1;

}

// Called when the game starts or when spawned
void ADestructibleElements::BeginPlay(){
	Super::BeginPlay();

	DestructibleMesh->OnComponentFracture.AddDynamic(this,&ADestructibleElements::OnComponentFracture);

}

// Called every frame
void ADestructibleElements::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

}

void ADestructibleElements::HitMesh(const FHitResult& Hit) {

	if(ComplementaryActor != nullptr && ComplementaryActor->bSolved)
		return;

	CurrentDamage += 1;

	if(Health == 0 || Health == CurrentDamage){
		DestructibleMesh->ApplyDamage(3.f,Hit.ImpactPoint, Hit.ImpactPoint, 3000);	
		bSolved = true;
	}

}


void ADestructibleElements::OnComponentFracture(const FVector& HitPoint, const FVector& HitDirection) {
	AGameModeTutorial* GameMode = Cast<AGameModeTutorial>(GetWorld()->GetAuthGameMode());
	Collider->SetCollisionProfileName(TEXT("IgnorePawnProjectile"),false);
	bIAmDestroyed = true;

	if(DoorsToOpen.Num() > 0){
		for(ADoor* Door: DoorsToOpen)
			Door->bOpenDoor = true;
	}

}
