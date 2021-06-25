// Fill out your copyright notice in the Description page of Project Settings.


#include "AllyQuadAIController.h"
#include "BehaviorTree/BlackBoardComponent.h"


void AAllyQuadAIController::BeginPlay() {
    
    Super::BeginPlay();
    
    if(BTree != nullptr){
        RunBehaviorTree(BTree);
    }else
        UE_LOG(LogTemp,Warning,TEXT("No Behavior Tree"));
    
}

void AAllyQuadAIController::Tick(float DeltaTime) {

    if(GetPawn() != nullptr && !FirstTime){

        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"),GetPawn()->GetActorLocation());
        GetBlackboardComponent()->SetValueAsBool(TEXT("NotEIsPressed"),true);
        FirstTime = true;

    }

}
