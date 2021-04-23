// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomPlayerStart.h"
#include "COmponents/CapsuleComponent.h"

void ACustomPlayerStart::BeginPlay() {    
    UCapsuleComponent* CapsuleCollider = FindComponentByClass<UCapsuleComponent>();    
    CapsuleCollider->SetMobility(EComponentMobility::Movable);
}
