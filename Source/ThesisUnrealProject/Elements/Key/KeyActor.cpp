// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyActor.h"

// Sets default values
AKeyActor::AKeyActor(){

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	RotationSpeed = 1.f;

}

// Called when the game starts or when spawned
void AKeyActor::BeginPlay(){

	Super::BeginPlay();

	Mesh->OnComponentBeginOverlap.AddDynamic(this,&AKeyActor::OnKeyOverlap);
	
}

// Called every frame
void AKeyActor::Tick(float DeltaTime){

	Super::Tick(DeltaTime);
	
	AddActorWorldRotation(FRotator(0.f,RotationSpeed * DeltaTime, 0.f));

}

void AKeyActor::OnKeyOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit) {
	
	if(OtherActor->IsA(APawn::StaticClass()) && Cast<APawn>(OtherActor)->GetController()->IsA(APlayerController::StaticClass())){
		
		KeyDelegate.Broadcast();
		Destroy();

	}

}

