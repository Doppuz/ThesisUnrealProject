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

	ID = 0;
	Health = 3;
	CurrentDamage = 0;
	ShakeSpeed = 50.f;
	ShakeDistance = 100.f;
	IntervalTime = 2.f;
	bCanShake = false;
}

// Called when the game starts or when spawned
void ADestructibleElements::BeginPlay(){
	Super::BeginPlay();
	
	StartPosition = GetActorLocation();

	DestructibleMesh->OnComponentFracture.AddDynamic(this,&ADestructibleElements::OnComponentFracture);

	if(bCanShake){
		WaitShake();
	}

}

// Called every frame
void ADestructibleElements::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

	if(bIsShaking){
		if(GetActorLocation().Y >= StartPosition.Y + ShakeDistance || GetActorLocation().Y <= StartPosition.Y - ShakeDistance){
			ShakeSpeed = -ShakeSpeed;
			AddActorLocalOffset(GetActorRightVector() * ShakeSpeed * DeltaTime);
		}else{
			AddActorLocalOffset(GetActorRightVector() * ShakeSpeed * DeltaTime);
		}
	}else{
		SetActorLocation(StartPosition);
	}

}

void ADestructibleElements::HitMesh(const FHitResult& Hit) {

	if(ComplementaryActor != nullptr && ComplementaryActor->bSolved)
		return;

	CurrentDamage += 1;
	
	if(Health == CurrentDamage){
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

void ADestructibleElements::Shake() {
	bIsShaking = true;	
	GetWorld()->GetTimerManager().SetTimer(ShakeTimer,this,&ADestructibleElements::WaitShake,IntervalTime,false);
}

void ADestructibleElements::WaitShake() {
	bIsShaking = false;	
	GetWorld()->GetTimerManager().SetTimer(ShakeTimer,this,&ADestructibleElements::Shake,IntervalTime,false);
}
