// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleButton.h"
#include "Components/BoxComponent.h"
#include "../../GameModeTutorial.h"

// Sets default values
APuzzleButton::APuzzleButton(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Collider->SetupAttachment(RootComponent);
	
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Trigger->SetupAttachment(RootComponent);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collider);

	bDisableOverlap = false;
	bIsPressed = false;
}

// Called when the game starts or when spawned
void APuzzleButton::BeginPlay(){
	Super::BeginPlay();
	Trigger->OnComponentBeginOverlap.AddDynamic(this,&APuzzleButton::OnOverlap);
}

// Called every frame
void APuzzleButton::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

}

void APuzzleButton::OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit) {
	AGameModeTutorial* GameMode = Cast<AGameModeTutorial>(GetWorld()->GetAuthGameMode());

	if(OtherActor->IsA(APawn::StaticClass())){

		if(Cast<APawn>(OtherActor)->GetController()->IsA(APlayerController::StaticClass())){

			if(!bDisableOverlap){
			
				bDisableOverlap = true;
				Mesh->SetMaterial(0,ButtonColor);
				Overlap.Broadcast();
			
				//if(GetParentActor() != nullptr && GetParentActor()->IsA(APuzzleWith2Doors::StaticClass())){
					
				//}
			
			}
			
		}
	}
	
}

int APuzzleButton::GetID() {
	return ID;
}

