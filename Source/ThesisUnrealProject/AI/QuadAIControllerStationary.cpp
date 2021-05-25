// Fill out your copyright notice in the Description page of Project Settings.


#include "QuadAIControllerStationary.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "../Character/CharacterPawnQuad.h"

void AQuadAIControllerStationary::BeginPlay() {
    
    Super::BeginPlay();
    
    if(BTree != nullptr){
        RunBehaviorTree(BTree);
        APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"),GetPawn()->GetActorLocation());
    }else
        UE_LOG(LogTemp,Warning,TEXT("No Behavior Tree"));

    MovementValue = 1.f;

}

void AQuadAIControllerStationary::Tick(float DeltaTime) {
    
    Super::Tick(DeltaTime);

    ACharacterPawnQuad* MyPawn = Cast<ACharacterPawnQuad>(GetPawn());

    if(!MyPawn->bStationary){
        MyPawn->AddActorLocalOffset(FVector(0,MovementValue,0) * DeltaTime * 30);
    }

}
