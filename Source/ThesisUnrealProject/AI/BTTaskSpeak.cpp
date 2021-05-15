// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskSpeak.h"
#include "AllyQuadAIController.h"
#include "../Character/PawnAllyNPC.h"


UBTTaskSpeak::UBTTaskSpeak() {
    NodeName = "Speak";
}

EBTNodeResult::Type UBTTaskSpeak::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
    Super::ExecuteTask(OwnerComp,NodeMemory);

    AAllyQuadAIController* AIController = Cast<AAllyQuadAIController>(OwnerComp.GetAIOwner());

    if(AIController == nullptr)
        return EBTNodeResult::Failed;

    APawnAllyNPC* AIPawn = Cast<APawnAllyNPC>(AIController->GetPawn());
    AIPawn->Speak();
    return EBTNodeResult::Succeeded;
}
