// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskEquipment.h"
#include "AllyQuadAIController.h"
#include "../Character/PawnAllyNPC.h"


UBTTaskEquipment::UBTTaskEquipment() {
    NodeName = "Equipment";
}

EBTNodeResult::Type UBTTaskEquipment::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
    Super::ExecuteTask(OwnerComp,NodeMemory);

    AAllyQuadAIController* AIController = Cast<AAllyQuadAIController>(OwnerComp.GetAIOwner());

    if(AIController == nullptr)
        return EBTNodeResult::Failed;

    APawnAllyNPC* AIPawn = Cast<APawnAllyNPC>(AIController->GetPawn());
    //AIPawn->Equipment();
    return EBTNodeResult::Succeeded;
}
