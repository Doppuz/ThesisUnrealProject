// Fill out your copyright notice in the Description page of Project Settings.


#include "Trap.h"
#include "../Character/CharacterPawnQuad.h"

// Sets default values
ATrap::ATrap(){

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ATrap::BeginPlay(){

	Super::BeginPlay();
	
	Mesh->OnComponentHit.AddDynamic(this, &ATrap::OnHit);

}

void ATrap::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {
	
	if(OtherActor->IsA(ACharacterPawnQuad::StaticClass())){
	
		FPointDamageEvent DamageEvent(10,Hit,this->GetVelocity(),nullptr);
		OtherActor->TakeDamage(10, DamageEvent,nullptr,this);
	
	}

}