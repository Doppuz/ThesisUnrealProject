// Fill out your copyright notice in the Description page of Project Settings.


#include "Portal.h"
#include "../../Character/CharacterPawnQuad.h"
#include "../../GameModeAbstract.h"
#include "../../UI/UIWidgetDialog.h"
 #include "Components/ProgressBar.h"

// Sets default values
APortal::APortal(){

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collider"));
	Collider->SetupAttachment(RootComponent);

	Particles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particles"));
	Particles->SetupAttachment(Collider);

}

// Called when the game starts or when spawned
void APortal::BeginPlay(){

	Super::BeginPlay();

	Collider->OnComponentBeginOverlap.AddDynamic(this, &APortal::OnOverlap);

}

void APortal::OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit) {
	
	if(OtherActor->IsA(ACharacterPawnQuad::StaticClass())){
		OtherActor->SetActorLocation(NewPosition);
		OtherActor->SetActorRotation(NewRotation);
        Cast<ACharacterPawnQuad>(OtherActor)->CurrentHealth = Cast<ACharacterPawnQuad>(OtherActor)->MaxHealth;
		AGameModeAbstract* GameMode = Cast<AGameModeAbstract>(GetWorld()->GetAuthGameMode());
		UUIWidgetDialog* DialogWidget = Cast<UUIWidgetDialog>(GameMode->GetCurrentWidgetUI());
		DialogWidget->HealthBar->SetPercent(1.f);
		Destroy();
	}

}


