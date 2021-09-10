// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_NewPosition.h"	
#include "AIController.h"
#include "../../Character/InterfaceMovableAI.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "Kismet/GameplayStatics.h"


UBTService_NewPosition::UBTService_NewPosition() {

    NodeName = "SetNewPosition";
    
}

void UBTService_NewPosition::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {

    if(OwnerComp.GetAIOwner()->GetPawn()->Implements<UInterfaceMovableAI>()){

        IInterfaceMovableAI* AIPawn = Cast<IInterfaceMovableAI>(OwnerComp.GetAIOwner()->GetPawn());

        float A = (OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation() - OwnerComp.GetBlackboardComponent()->GetValueAsVector("NewPosition")).Size();

        //Need to do like this because the service is shared with all the controllers.
        if((OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation() - OwnerComp.GetBlackboardComponent()->GetValueAsVector("NewPosition")).Size() < 100.f){

            if(OwnerComp.GetBlackboardComponent()->GetValueAsInt("Contator") == AIPawn->Positions.Num() -1)
                OwnerComp.GetBlackboardComponent()->SetValueAsBool("Direction", false);
            else if(OwnerComp.GetBlackboardComponent()->GetValueAsInt("Contator") == 0)
                OwnerComp.GetBlackboardComponent()->SetValueAsBool("Direction", true);

            if(OwnerComp.GetBlackboardComponent()->GetValueAsBool("Direction"))
                OwnerComp.GetBlackboardComponent()->SetValueAsInt("Contator",OwnerComp.GetBlackboardComponent()->GetValueAsInt("Contator") + 1); 
            else
                OwnerComp.GetBlackboardComponent()->SetValueAsInt("Contator",OwnerComp.GetBlackboardComponent()->GetValueAsInt("Contator") - 1); 

            if(AIPawn->Positions.Num() > 0)
                OwnerComp.GetBlackboardComponent()->SetValueAsVector("NewPosition",AIPawn->Positions[OwnerComp.GetBlackboardComponent()->GetValueAsInt("Contator")] + FVector(0.f,0.f,-16.f)); //Just for beeing a little be smoother.

        }

    }else{

        UE_LOG(LogTemp,Warning,TEXT("Error in ServiceNewPosition : No Movable interface implemented"));

    }

}
