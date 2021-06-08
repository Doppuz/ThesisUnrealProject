// Fill out your copyright notice in the Description page of Project Settings.


#include "QuadAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackBoardComponent.h"

void AQuadAIController::BeginPlay() {
    
    Super::BeginPlay();
    
    if(BTree != nullptr){
        RunBehaviorTree(BTree);
    }else
        UE_LOG(LogTemp,Warning,TEXT("No Behavior Tree"));

}

void AQuadAIController::Tick(float DeltaTime) {
    
    Super::Tick(DeltaTime);
    
}
