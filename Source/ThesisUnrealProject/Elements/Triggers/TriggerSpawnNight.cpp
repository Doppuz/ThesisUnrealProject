// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerSpawnNight.h"
#include "Components/BoxComponent.h"
#include "../../Character/CharacterPawnQuad.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/LevelStreaming.h"
#include "Components/SpotLightComponent.h"

// Sets default values
ATriggerSpawnNight::ATriggerSpawnNight(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	LightOn = true;
	AttenuationRadius = 1000.f;

}

void ATriggerSpawnNight::OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit) {
	
	if(OtherActor->IsA(ACharacterPawnQuad::StaticClass())){
		ACharacterPawnQuad* MyPawn = Cast<ACharacterPawnQuad>(OtherActor);
		
		if(MyPawn->GetController()->IsA(APlayerController::StaticClass())){
    		FLatentActionInfo LatentInfo;

			if(!LightOn){
				
				UGameplayStatics::UnloadStreamLevel(this, TEXT("Day"), LatentInfo, true);
				MyPawn->SpotLight->Intensity = 100000.f;
				MyPawn->SpotLight->AttenuationRadius = AttenuationRadius;
				//UGameplayStatics::LoadStreamLevel(this, TEXT("Night"), true, true, LatentInfo);
				
			}else{
				
				//UGameplayStatics::UnloadStreamLevel(this, TEXT("Night"), LatentInfo, true);
				MyPawn->SpotLight->Intensity = 0.f;	
				UGameplayStatics::LoadStreamLevel(this, TEXT("Day"), true, true, LatentInfo);
			
			}

		}
	}

}