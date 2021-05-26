// Fill out your copyright notice in the Description page of Project Settings.


#include "AIBull.h"
#include "Components/BoxComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/GameplayStatics.h"
#include "../Character/CharacterPawnQuad.h"

// Sets default values
AAIBull::AAIBull()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	RootComponent = Collider;

	Collider->SetSimulatePhysics(true);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	PawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("PawnMovement"));
	PawnMovement->MaxSpeed = 300;
	PawnMovement->Acceleration = 1000;

	Collider->OnComponentHit.AddDynamic(this, &AAIBull::OnHit);

	Damage = 10.f;
}

// Called when the game starts or when spawned
void AAIBull::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAIBull::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetActorLocation(FVector(GetActorLocation().X,GetActorLocation().Y,42.f));
}

// Called to bind functionality to input
void AAIBull::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAIBull::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);

	if(OtherActor->IsA(ACharacterPawnQuad::StaticClass())){
		ACharacterPawnQuad* MyPawn = Cast<ACharacterPawnQuad>(OtherActor);
		if(MyPawn->GetController()->IsA(APlayerController::StaticClass())){
			FPointDamageEvent DamageEvent(Damage,Hit,this->GetVelocity(),nullptr);
			OtherActor->TakeDamage(Damage,DamageEvent,MyPawn->GetController(),this);
		}
	}



}

