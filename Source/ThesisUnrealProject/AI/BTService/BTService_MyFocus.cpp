// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_MyFocus.h"	
#include "AIController.h"
#include "../../Character/InterfaceMovableAI.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "Kismet/GameplayStatics.h"


UBTService_MyFocus::UBTService_MyFocus() {

    NodeName = "SetFocus";
    
}

void UBTService_MyFocus::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {

    if(OwnerComp.GetAIOwner()->GetPawn()->Implements<UInterfaceMovableAI>()){

        IInterfaceMovableAI* AIPawn = Cast<IInterfaceMovableAI>(OwnerComp.GetAIOwner()->GetPawn());

        FVector Direction = Cast<APawn>(AIPawn)->GetActorLocation() - OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey());
        Direction.Z = 0.f;

        Cast<APawn>(AIPawn)->SetActorRotation(Direction.Rotation());

    }else{

        UE_LOG(LogTemp,Warning,TEXT("Error in ServiceNewPosition : No Movable interface implemented"));

    }

}
