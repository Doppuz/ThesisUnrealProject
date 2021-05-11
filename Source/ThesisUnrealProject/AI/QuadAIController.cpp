// Fill out your copyright notice in the Description page of Project Settings.


#include "QuadAIController.h"
#include "Kismet/GameplayStatics.h"

void AQuadAIController::BeginPlay() {
    
    Super::BeginPlay();

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);

    SetFocus(PlayerPawn);
    
    MoveToActor(PlayerPawn);

}

void AQuadAIController::Tick(float DeltaTime) {
    
    Super::Tick(DeltaTime);
    
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);

    if(LineOfSightTo(PlayerPawn)){
        SetFocus(PlayerPawn);
        MoveToActor(PlayerPawn,200);
    }else{
        ClearFocus(EAIFocusPriority::Gameplay);
        StopMovement();
    }
}
