// Fill out your copyright notice in the Description page of Project Settings.


#include "Storm.h"
#include "../../Character/CharacterPawnQuad.h"

// Sets default values
AStorm::AStorm(){

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collider"));
	Collider->SetupAttachment(RootComponent);

	Particles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particles"));
	Particles->SetupAttachment(Root);

	CurrentIndex = 1;
	StraightDirection = true;
	Speed = 200.f;

}

// Called when the game starts or when spawned
void AStorm::BeginPlay(){
	Super::BeginPlay();

	if(StraightDirection)
		SetActorLocation(Positions[0]);
	else
		SetActorLocation(Positions[2]);

		Collider->OnComponentBeginOverlap.AddDynamic(this,&AStorm::OnOverlap);
	
}

// Called every frame
void AStorm::Tick(float DeltaTime){

	Super::Tick(DeltaTime);

	FVector Vector = Positions[CurrentIndex] - GetActorLocation();
	Vector.Normalize();

	AddActorWorldOffset(Vector * DeltaTime * Speed);

	if((Positions[CurrentIndex] - GetActorLocation()).Size() < 5.f){
		
		if(CurrentIndex == 0)
			StraightDirection = true;
		
		if(CurrentIndex == 2)
			StraightDirection = false;

		if(StraightDirection)
			CurrentIndex += 1;
		else
			CurrentIndex -= 1;

	}

}

void AStorm::OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit){

	if(OtherActor->IsA(ACharacterPawnQuad::StaticClass())){
	
		FPointDamageEvent DamageEvent(10.f,Hit,this->GetVelocity(),nullptr);
		OtherActor->TakeDamage(10.f,DamageEvent,GetController(),this);
	
	}

}