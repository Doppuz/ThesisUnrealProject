// Fill out your copyright notice in the Description page of Project Settings.


#include "DestructibleElements.h"
#include "DestructibleComponent.h"
#include "../GameModeTutorial.h"

// Sets default values
ADestructibleElements::ADestructibleElements(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	DestructibleMesh = CreateDefaultSubobject<UDestructibleComponent>(TEXT("DestructibleMesh"));
	DestructibleMesh->SetupAttachment(RootComponent);

	ID = 0;
}

// Called when the game starts or when spawned
void ADestructibleElements::BeginPlay()
{
	Super::BeginPlay();
	
	DestructibleMesh->OnComponentFracture.AddDynamic(this,&ADestructibleElements::OnComponentFracture);
}

// Called every frame
void ADestructibleElements::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ADestructibleElements::OnComponentFracture(const FVector& HitPoint, const FVector& HitDirection) {
	AGameModeTutorial* GameMode = Cast<AGameModeTutorial>(GetWorld()->GetAuthGameMode());
		
		switch(ID){
			case 0:
				//Case 0 is the choice of the first puzzle. I want to avoid to solve the puzzle after the gate is destroyed.
				GameMode->bGateDestroyed = true;
			break;
			default:
				UE_LOG(LogTemp,Warning,TEXT("Error in squaredProjectile, no ID for this Destr Component"));
		}

}
