// Fill out your copyright notice in the Description page of Project Settings.


#include "GunController.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "../Elements/CrateElements.h"
#include "DestructibleComponent.h"

// Sets default values
AGunController::AGunController(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));
	SkeletalMesh->SetupAttachment(RootComponent);

	MaxRange = 10000;

}

void AGunController::PullTrigger() {
	UGameplayStatics::SpawnEmitterAttached(MuzzleEffect,SkeletalMesh,TEXT("MuzzleFlashSocket"));

	APawn* Pawn = Cast<APawn>(GetOwner());
	AController* PawnController = Cast<AController>(Pawn->GetController());
	
	FVector Position;
	FRotator Rotation;
	PawnController->GetPlayerViewPoint(Position,Rotation);

	FVector End = Position + Rotation.Vector() * MaxRange;

	FHitResult Hit;

	FCollisionQueryParams Params(NAME_None, true, Pawn);

	bool bSucc = GetWorld()->LineTraceSingleByChannel(Hit,Position,End,ECollisionChannel::ECC_GameTraceChannel3,Params);


	if(bSucc){
		FVector ShotDirection = -Rotation.Vector();
		
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),ImpactEffect, Hit.Location,ShotDirection.Rotation(),FVector(3,3,3));

		if(Hit.GetActor()->IsA(ACrateElements::StaticClass()) && Hit.GetComponent()->IsA(UDestructibleComponent::StaticClass())){
			//UGameplayStatics::ApplyDamage(OtherActor,10,this->GetController(),this,UDamageType::StaticClass());
			UDestructibleComponent* DC = Cast<UDestructibleComponent>(Hit.GetComponent());
			ACrateElements* Actor = Cast<ACrateElements>(Hit.GetActor());
		
			if(!Actor->IAmDestructed)
				DC->ApplyRadiusDamage(100.f,Hit.ImpactPoint, 100.f,50000.f,true);
		}
	}
}

// Called when the game starts or when spawned
void AGunController::BeginPlay(){
	Super::BeginPlay();
}

// Called every frame
void AGunController::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
}

