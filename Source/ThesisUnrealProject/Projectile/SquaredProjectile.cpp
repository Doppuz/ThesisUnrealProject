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

	MovementProjectile->InitialSpeed = 1000.F;
	MovementProjectile->MaxSpeed = 1000.F;

	Damage = 10.f;
}

// Called when the game starts or when spawned
void ASquaredProjectile::BeginPlay(){
	Super::BeginPlay();
	
	Collider->OnComponentBeginOverlap.AddDynamic(this, &ASquaredProjectile::OnOverlap);
}

void ASquaredProjectile::OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit) {

	if(OtherActor->IsA(ADestructibleElements::StaticClass())){

		ADestructibleElements* Actor = Cast<ADestructibleElements>(OtherActor);
		UDestructibleComponent* DC = Actor->DestructibleMesh;
		AGameModeTutorial* GameMode = Cast<AGameModeTutorial>(GetWorld()->GetAuthGameMode());
		
		switch(Actor->ID){
			case 0:
				//Case 0 is the choice of the first puzzle. I want to avoid to destroy the gate if I solved the puzzle.
				//if(!GameMode->bSolvedPuzzle1 && !Actor->bIAmDestroyed){
				Actor->HitMesh(Hit);
					//DC->ApplyRadiusDamage(1.f,Hit.ImpactPoint, 1.f,3000.f,true);
					//DC->ApplyDamage(1.1f,Hit.ImpactPoint, Hit.ImpactPoint, 30000);
				//}
			break;
			case 1:
				if(GameMode->bEnemyDefeated && !Actor->bIAmDestroyed)
					Actor->HitMesh(Hit);
				break;
			case 2:
				Actor->HitMesh(Hit);
			default:
				break;
		}

	}else if(OtherActor->IsA(APawn::StaticClass())){
		FPointDamageEvent DamageEvent(Damage,Hit,this->GetVelocity(),nullptr);
		if(MyOwner != nullptr){
			
			APawn* ShooterPawn = Cast<APawn>(MyOwner);
			APawn* OtherPawn = Cast<APawn>(OtherActor);

			if(OtherPawn != nullptr && OtherPawn->GetController() != nullptr &&OtherPawn->GetController()->IsA(APlayerController::StaticClass()))
				OtherActor->TakeDamage(Damage, DamageEvent,ShooterPawn->GetController(),this);

			if(ShooterPawn != nullptr && ShooterPawn->GetController() != nullptr &&ShooterPawn->GetController()->IsA(APlayerController::StaticClass()))
				OtherActor->TakeDamage(Damage, DamageEvent,ShooterPawn->GetController(),this);

			/*if(ShooterPawn != nullptr && OtherPawn != nullptr && 
				ShooterPawn->GetController() != nullptr && OtherPawn->GetController() != nullptr &&
					!((ShooterPawn->GetController()->IsA(AAIController::StaticClass())) && 
					OtherPawn->GetController()->IsA(AAIController::StaticClass()))){

				OtherActor->TakeDamage(Damage, DamageEvent,ShooterPawn->GetController(),this);

			}*/
		}
	}

	Destroy();
}

// Called every frame
void ASquaredProjectile::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

}