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

	ID = 0;
	Health = 3;
	CurrentDamage = 0;
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
	CurrentDamage += 1;
	if(Health == CurrentDamage)
		DestructibleMesh->ApplyDamage(3.f,Hit.ImpactPoint, Hit.ImpactPoint, 3000);	
}


void ADestructibleElements::OnComponentFracture(const FVector& HitPoint, const FVector& HitDirection) {
	AGameModeTutorial* GameMode = Cast<AGameModeTutorial>(GetWorld()->GetAuthGameMode());
	Collider->SetCollisionProfileName(TEXT("IgnorePawnProjectile"),false);
	bIAmDestroyed = true;

		switch(ID){
			case 0:
				//Case 0 is the choice of the first puzzle. I want to avoid to solve the puzzle after the gate is destroyed.
				GameMode->bGateDestroyed = true;
			break;
			case 2:
				GameMode->SetDoorOpen(8);
				GameMode->SetDoorOpen(10);
			default:
				break;
				//UE_LOG(LogTemp,Warning,TEXT("Error in squaredProjectile, no ID for this Destr Component"));
		}

}
