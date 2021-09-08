// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_Timer.h"	
#include "AIController.h"
#include "../../Character/InterfaceMovableAI.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "Kismet/GameplayStatics.h"


UBTService_Timer::UBTService_Timer() {

    NodeName = "SetTimer";
    
}

void UBTService_Timer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {

    OwnerComp.GetBlackboardComponent()->SetValueAsBool("Timer", !OwnerComp.GetBlackboardComponent()->GetValueAsBool("Timer"));

}
