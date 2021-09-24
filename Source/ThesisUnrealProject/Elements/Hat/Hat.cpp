// Fill out your copyright notice in the Description page of Project Settings.


#include "Hat.h"
#include "../../Character/CharacterPawnQuad.h"

// Sets default values
AHat::AHat(){

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AHat::BeginPlay(){

	Super::BeginPlay();

	Mesh->OnComponentBeginOverlap.AddDynamic(this,&AHat::OnHatOverlap);
	
}

void AHat::OnHatOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit) {
	
	if(OtherActor->IsA(ACharacterPawnQuad::StaticClass())){

		Destroy();

	}

}

// Called every frame
void AHat::Tick(float DeltaTime){

	Super::Tick(DeltaTime);

}

