// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_MyFocus.h"	
#include "AIController.h"
#include "../../Character/InterfaceMovableAI.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../../Character/AllyAI/AICharacterPawnQuad.h"


UBTService_MyFocus::UBTService_MyFocus() {

    NodeName = "SetFocus";
    
}

void UBTService_MyFocus::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {

    if(GetSelectedBlackboardKey().IsValid()){

        FVector Direction = OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey()) - OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation();
        Direction.Z = 0;
        FRotator Rotator = Direction.Rotation();
        APawn* P = OwnerComp.GetAIOwner()->GetPawn();
            
        OwnerComp.GetAIOwner()->GetPawn()->SetActorRotation(Direction.Rotation());

    }

}
