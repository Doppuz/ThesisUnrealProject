// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerSpawnAlly.h"
#include "Components/BoxComponent.h"
#include "../../Character/AllyAI/AICharacterPawnQuad.h"
#include "../../Character/CharacterPawnQuad.h"

// Sets default values
ATriggerSpawnAlly::ATriggerSpawnAlly(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void ATriggerSpawnAlly::OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit) {

	if(OtherActor->IsA(ACharacterPawnQuad::StaticClass())){
		APawn* MyPawn = Cast<APawn>(OtherActor);
		if(MyPawn->GetController()->IsA(APlayerController::StaticClass())){
			AAICharacterPawnQuad* AIAlly = GetWorld()->SpawnActor<AAICharacterPawnQuad>(AllyClass,
				FVector(GetActorLocation().X,GetActorLocation().Y,MyPawn->GetActorLocation().Z)
				,GetActorRotation());
			Destroy();
		}
	}

}

