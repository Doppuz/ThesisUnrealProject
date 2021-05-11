// Fill out your copyright notice in the Description page of Project Settings.


#include "SquaredProjectile.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "../Elements/DestructibleElements.h"
#include "DestructibleComponent.h"
#include "../GameModeTutorial.h"

// Sets default values
ASquaredProjectile::ASquaredProjectile(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	RootComponent = Collider;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	MovementProjectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
}

// Called when the game starts or when spawned
void ASquaredProjectile::BeginPlay(){
	Super::BeginPlay();
	
	Collider->OnComponentHit.AddDynamic(this, &ASquaredProjectile::OnHit);
}

// Called every frame
void ASquaredProjectile::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

}

void ASquaredProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {
	if(OtherActor->IsA(ADestructibleElements::StaticClass()) && OtherComponent->IsA(UDestructibleComponent::StaticClass())){

		UDestructibleComponent* DC = Cast<UDestructibleComponent>(OtherComponent);
		ADestructibleElements* Actor = Cast<ADestructibleElements>(OtherActor);
		AGameModeTutorial* GameMode = Cast<AGameModeTutorial>(GetWorld()->GetAuthGameMode());
		

		switch(Actor->ID){
			case 0:
				//Case 0 is the choice of the first puzzle. I want to avoid to destroy the gate if I solved the puzzle.
				if(!GameMode->bSolvedPuzzle1 && !GameMode->bGateDestroyed)
					DC->ApplyRadiusDamage(1.f,Hit.ImpactPoint, 1.f,50000.f,true);
			break;
			default:
				UE_LOG(LogTemp,Warning,TEXT("Error in squaredProjectile, no ID for this Destr Component"));
		}
	}

	Destroy();
}
