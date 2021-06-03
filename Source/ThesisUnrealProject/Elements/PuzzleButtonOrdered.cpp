// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleButtonOrdered.h"
#include "Components/BoxComponent.h"
#include "../GameModeTutorial.h"

// Sets default values
APuzzleButtonOrdered::APuzzleButtonOrdered(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

void APuzzleButtonOrdered::OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit) {
	AGameModeTutorial* GameMode = Cast<AGameModeTutorial>(GetWorld()->GetAuthGameMode());
	
	if(OtherActor->IsA(APawn::StaticClass())){

		if(Cast<APawn>(OtherActor)->GetController()->IsA(APlayerController::StaticClass())){

			if(!bDisableOverlap){
				bDisableOverlap = true;
				Mesh->SetMaterial(0,ButtonColor);
				GameMode->ElemsPuzzle.Add(this);
			}
		}
	}
	
}


