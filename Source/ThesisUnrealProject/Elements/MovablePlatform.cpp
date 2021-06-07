// Fill out your copyright notice in the Description page of Project Settings.


#include "MovablePlatform.h"
#include "Components/BoxComponent.h"

// Sets default values
AMovablePlatform::AMovablePlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	PlatformCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Coin Collider"));
	PlatformCollider->SetupAttachment(RootComponent);

	PlatformCollider->SetCollisionProfileName("BlockAll");

	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Coin Mesh"));
	PlatformMesh->SetupAttachment(PlatformCollider);

	Triggers = CreateDefaultSubobject<USceneComponent>(TEXT("Triggers"));
	Triggers->SetupAttachment(RootComponent);
	
	FirstBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TopBox"));
	FirstBox->SetupAttachment(Triggers);

	SecondBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BotBox"));
	SecondBox->SetupAttachment(Triggers);

	bHorizontalMovement = true;
	Speed = 100.f;
}

// Called when the game starts or when spawned
void AMovablePlatform::BeginPlay(){

	Super::BeginPlay();

	PlatformCollider->OnComponentBeginOverlap.AddDynamic(this, &AMovablePlatform::OnOverlap);

}

// Called every frame
void AMovablePlatform::Tick(float DeltaTime){
	
	Super::Tick(DeltaTime);

	if(bHorizontalMovement){
		PlatformCollider->AddLocalOffset(PlatformCollider->GetForwardVector() * Speed * DeltaTime);
	}
}

void AMovablePlatform::OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit) {
	
	if(OtherActor->IsA(AMovablePlatform::StaticClass()) && OtherComponent->IsA(UBoxComponent::StaticClass()))
		Speed = -Speed;

}

