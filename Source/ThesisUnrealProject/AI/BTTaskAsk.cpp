// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskAsk.h"
#include "AllyQuadAIController.h"
#include "../Character/PawnAllyNPC.h"


UBTTaskAsk::UBTTaskAsk() {
    NodeName = "Ask";
}

EBTNodeResult::Type UBTTaskAsk::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
    Super::ExecuteTask(OwnerComp,NodeMemory);

    AAllyQuadAIController* AIController = Cast<AAllyQuadAIController>(OwnerComp.GetAIOwner());

    if(AIController == nullptr)
        return EBTNodeResult::Failed;

    APawnAllyNPC* AIPawn = Cast<APawnAllyNPC>(AIController->GetPawn());
    AIPawn->Ask();
    return EBTNodeResult::Succeeded;
}
