// Fill out your copyright notice in the Description page of Project Settings.


#include "PortalNight.h"
#include "../../Character/CharacterPawnQuad.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SpotLightComponent.h"
#include "Engine/LevelStreaming.h"


void APortalNight::BeginPlay() {
    
    Super::BeginPlay();

}


void APortalNight::OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit) {
    
    Super::OnOverlap(HitComponent, OtherActor, OtherComponent, otherBodyIndex, fromsweep, Hit);

    if(OtherActor->IsA(ACharacterPawnQuad::StaticClass())){
        
        FLatentActionInfo LatentInfo;
        ACharacterPawnQuad* MyPawn = Cast<ACharacterPawnQuad>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));

        UGameplayStatics::UnloadStreamLevel(this, TEXT("Day"), LatentInfo, true);
		MyPawn->SpotLight->Intensity = 100000.f;
		MyPawn->SpotLight->AttenuationRadius = 3500.f;

    }
    
}

