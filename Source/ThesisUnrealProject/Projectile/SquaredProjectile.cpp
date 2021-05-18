// Fill out your copyright notice in the Description page of Project Settings.


#include "SquaredProjectile.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "../Elements/DestructibleElements.h"
#include "DestructibleComponent.h"
#include "../GameModeTutorial.h"
#include "../Character/CharacterPawnQuad.h"
#include "../AI/QuadAIController.h"

// Sets default values
ASquaredProjectile::ASquaredProjectile(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	RootComponent = Collider;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	MovementProjectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));

	Damage = 10.f;
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
	if(OtherActor->IsA(ADestructibleElements::StaticClass())){

		ADestructibleElements* Actor = Cast<ADestructibleElements>(OtherActor);
		UDestructibleComponent* DC = Actor->DestructibleMesh;
		AGameModeTutorial* GameMode = Cast<AGameModeTutorial>(GetWorld()->GetAuthGameMode());
		
		switch(Actor->ID){
			case 0:
				//Case 0 is the choice of the first puzzle. I want to avoid to destroy the gate if I solved the puzzle.
				if(!GameMode->bSolvedPuzzle1 && !Actor->bIAmDestroyed){
					Actor->HitMesh(Hit);
					//DC->ApplyRadiusDamage(1.f,Hit.ImpactPoint, 1.f,3000.f,true);
					//DC->ApplyDamage(1.1f,Hit.ImpactPoint, Hit.ImpactPoint, 30000);
				}
			break;
			case 1:
				if(GameMode->bEnemyDefeated && !Actor->bIAmDestroyed)
					Actor->HitMesh(Hit);
				break;
			default:
				UE_LOG(LogTemp,Warning,TEXT("Error in squaredProjectile, no ID for this Destr Component"));
				break;
		}

	}else if(OtherActor->IsA(ACharacterPawnQuad::StaticClass())){
		FPointDamageEvent DamageEvent(Damage,Hit,this->GetVelocity(),nullptr);
		if(MyOwner != nullptr){
			ACharacterPawnQuad* MyPawn = Cast<ACharacterPawnQuad>(MyOwner);

			if(MyPawn != nullptr)
				OtherActor->TakeDamage(Damage, DamageEvent,MyPawn->GetController(),this);
		}
	}

	Destroy();
}
