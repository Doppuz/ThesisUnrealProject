// Fill out your copyright notice in the Description page of Project Settings.


#include "ShakeActorFallen.h"
#include "../Elements/Platforms/FallenPlatform.h"

void AShakeActorFallen::Shake(float DeltaTime) {
    
    if(!Cast<AFallenPlatform>(ShakingActor->GetChildActor())->bFall){
        if(bIsShaking){
            
            if(ShakeLeft)
                ShakingActor->AddLocalOffset(ShakingActor->GetRightVector() * ShakeSpeed);
            else
                ShakingActor->AddLocalOffset(ShakingActor->GetForwardVector() * ShakeSpeed);
        }else{
            SetActorLocation(StartPosition);
        }
    }
    
}
