// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrolAIController.h"
#include "BehaviorTree/BlackBoardComponent.h"

APatrolAIController::APatrolAIController() {
    
	PrimaryActorTick.bCanEverTick = false;

}

void APatrolAIController::BeginPlay() {
    
    Super::BeginPlay();
    
    if(BTree != nullptr){
        RunBehaviorTree(BTree);
    }else
        UE_LOG(LogTemp,Warning,TEXT("No Behavior Tree"));
    
}

