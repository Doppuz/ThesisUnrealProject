// Fill out your copyright notice in the Description page of Project Settings.


#include "SquaredProjectile.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "../Elements/DestructibleElements.h"
#include "DestructibleComponent.h"
#include "../GameModeTutorial.h"
#include "../Character/CharacterPawnQuad.h"
#include "../AI/QuadAIController.h"
#include "../Character/AICharacterPawnQuad.h"
#include "../Elements/CrateElements.h"

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
		
		if(Cast<APawn>(MyOwner)->GetController()->IsA(APlayerController::StaticClass()))
			Actor->HitMesh(Hit);
		
	}else if(OtherActor->IsA(APawn::StaticClass())){
		FPointDamageEvent DamageEvent(Damage,Hit,this->GetVelocity(),nullptr);
		if(MyOwner != nullptr){
			
			APawn* ShooterPawn = Cast<APawn>(MyOwner);
			APawn* OtherPawn = Cast<APawn>(OtherActor);

			//I can't hit myself
			if(ShooterPawn == OtherPawn)
				return;

			if(ShooterPawn != nullptr && ShooterPawn->IsA(AAICharacterPawnQuad::StaticClass())){ 

				if(OtherPawn != nullptr && OtherPawn->GetController() != nullptr && !OtherPawn->GetController()->IsA(APlayerController::StaticClass())){
					OtherActor->TakeDamage(Damage, DamageEvent,ShooterPawn->GetController(),this);
				}

			}else if(OtherPawn != nullptr && OtherPawn->GetController() != nullptr && OtherPawn->GetController()->IsA(APlayerController::StaticClass())){

				OtherActor->TakeDamage(Damage, DamageEvent,ShooterPawn->GetController(),this);


			}else if(ShooterPawn != nullptr && ShooterPawn->GetController() != nullptr && ShooterPawn->GetController()->IsA(APlayerController::StaticClass())){

				OtherActor->TakeDamage(Damage, DamageEvent,ShooterPawn->GetController(),this);


			}	

			/*if(ShooterPawn != nullptr && OtherPawn != nullptr && 
				ShooterPawn->GetController() != nullptr && OtherPawn->GetController() != nullptr &&
					!((ShooterPawn->GetController()->IsA(AAIController::StaticClass())) && 
					OtherPawn->GetController()->IsA(AAIController::StaticClass()))){

				OtherActor->TakeDamage(Damage, DamageEvent,ShooterPawn->GetController(),this);

			}*/
		}
	}else if(OtherActor->IsA(ACrateElements::StaticClass())){
		
		Cast<ACrateElements>(OtherActor)->DestructibleComponent->ApplyDamage(3.f,Hit.ImpactPoint, Hit.ImpactPoint, 30000);	
	
	}
	Destroy();
}

// Called every frame
void ASquaredProjectile::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

}