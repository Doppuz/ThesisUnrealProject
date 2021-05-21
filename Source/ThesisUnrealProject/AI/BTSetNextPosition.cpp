// Fill out your copyright notice in the Description page of Project Settings.


#include "BTSetNextPosition.h"
#include "AllyQuadAIController.h"
#include "../Character/PawnInteractiveMove.h"
#include "BehaviorTree/BlackBoardComponent.h"


UBTSetNextPosition::UBTSetNextPosition() {
    NodeName = "Ask";
    Horizontal = 500;
    Vertical = 0;
}

EBTNodeResult::Type UBTSetNextPosition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
    Super::ExecuteTask(OwnerComp,NodeMemory);


    FVector StartLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(TEXT("StartLocation"));


    OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("NextLocation"),StartLocation + FVector(Horizontal,Vertical,0));

    Horizontal = -Horizontal;
    Vertical = -Vertical;

    UE_LOG(LogTemp,Warning,TEXT("%f"),Horizontal);

    return EBTNodeResult::Succeeded;
}
