// Fill out your copyright notice in the Description page of Project Settings.


#include "SquaredProjectile.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "../Elements/DestructibleElements.h"
#include "DestructibleComponent.h"

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
		//UGameplayStatics::ApplyDamage(OtherActor,10,this->GetController(),this,UDamageType::StaticClass());
		UDestructibleComponent* DC = Cast<UDestructibleComponent>(OtherComponent);
		//ACrateElements* Actor = Cast<ACrateElements>(OtherActor);
		
		//if(!Actor->IAmDestructed)
		//DC->ApplyDamage(1.f,Hit.ImpactPoint,Hit.ImpactPoint,50000.f);
		DC->ApplyRadiusDamage(1.f,Hit.ImpactPoint, 1000.f,50000.f,true);
	}

	Destroy();
}
