// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_TimerOff.h"	
#include "AIController.h"
#include "../../Character/InterfaceMovableAI.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "Kismet/GameplayStatics.h"


UBTService_TimerOff::UBTService_TimerOff() {

    NodeName = "SetTimer";
    
}

void UBTService_TimerOff::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {

    OwnerComp.GetBlackboardComponent()->SetValueAsBool("Timer", false);
}
