// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomPlayerStart.h"
#include "Components/CapsuleComponent.h"

void ACustomPlayerStart::BeginPlay() {    

    Super::BeginPlay();

    UCapsuleComponent* CapsuleCollider = FindComponentByClass<UCapsuleComponent>();    
    CapsuleCollider->SetMobility(EComponentMobility::Movable);
}
