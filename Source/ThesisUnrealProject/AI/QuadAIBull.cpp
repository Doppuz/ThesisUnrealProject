// Fill out your copyright notice in the Description page of Project Settings.


#include "QuadAIBull.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "../Character/CharacterPawnQuad.h"

void AQuadAIBull::BeginPlay() {
    
    Super::BeginPlay();
    
    if(BTree != nullptr){
        RunBehaviorTree(BTree);
        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"),FVector(GetPawn()->GetActorLocation().X,
                                                                                 GetPawn()->GetActorLocation().Y,
                                                                                 42.f));
                                                                                 
    }else
        UE_LOG(LogTemp,Warning,TEXT("No Behavior Tree"));

}

void AQuadAIBull::Tick(float DeltaTime) {
    
    Super::Tick(DeltaTime);

    //float Distance = (GetPawn()->GetActorLocation() - GetBlackboardComponent()->GetValueAsVector(TEXT("StartLocation"))).Size();
    //UE_LOG(LogTemp,Warning,TEXT("%f"),GetPawn()->GetVelocity().Size());
}