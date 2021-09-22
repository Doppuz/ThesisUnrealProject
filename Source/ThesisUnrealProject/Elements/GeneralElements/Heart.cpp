// Fill out your copyright notice in the Description page of Project Settings.


#include "Heart.h"
#include "../../Character/CharacterPawnQuad.h"

// Sets default values
AHeart::AHeart(){

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(Root);

	RotationSpeed = 2.f;

}

// Called when the game starts or when spawned
void AHeart::BeginPlay(){

	Super::BeginPlay();

	Mesh->OnComponentBeginOverlap.AddDynamic(this,&AHeart::OnCoinOverlap);

}


// Called every frame
void AHeart::Tick(float DeltaTime){

	Super::Tick(DeltaTime);

	AddActorLocalRotation(FRotator(0.f,RotationSpeed,0.f));

}

void AHeart::OnCoinOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit) {
	
	if(OtherActor->IsA(ACharacterPawnQuad::StaticClass())){
		Cast<ACharacterPawnQuad>(OtherActor)->IncreaseHealth(10.f);
		Destroy();
	}

}
