// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstaclePlatform.h"
#include "Components/BoxComponent.h"
#include "../Character/CharacterPawnQuad.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AObstaclePlatform::AObstaclePlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	RootComponent = Collider;

	Mesh1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh1->SetupAttachment(Collider);

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Trigger->SetupAttachment(Collider);
}


// Called when the game starts or when spawned
void AObstaclePlatform::BeginPlay(){
	Super::BeginPlay();

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AObstaclePlatform::OnOverlap);
	
}

void AObstaclePlatform::OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit) {

	if(OtherActor->IsA(ACharacterPawnQuad::StaticClass())){
		UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
	}

}

