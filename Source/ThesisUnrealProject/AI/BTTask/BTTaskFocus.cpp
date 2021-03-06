// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskFocus.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "../Controller/QuadAIController.h"
#include "../../Character/CharacterPawnQuad.h"

UBTTaskFocus::UBTTaskFocus() {
    NodeName = "Focus";
}

EBTNodeResult::Type UBTTaskFocus::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory){
    
    Super::ExecuteTask(OwnerComp,NodeMemory);

    OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("Focus"),bFocus);

    return EBTNodeResult::Succeeded;
}
