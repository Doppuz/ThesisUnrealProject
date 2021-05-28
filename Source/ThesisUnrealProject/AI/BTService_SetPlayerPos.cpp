// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SetPlayerPos.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "../Character/CharacterController.h"
#include "AIController.h"
#include "NavigationSystem.h"

UBTService_SetPlayerPos::UBTService_SetPlayerPos() {
    NodeName = "SetPlayerPosition";
    bRange = false;
    Range = 1000.f;
}

void UBTService_SetPlayerPos::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
    
    //If I activate the bRange bool, I set the value of the LineOfSight only if I the AI see me and within a specific range. 
    if(bRange){

        AAIController* AIController = OwnerComp.GetAIOwner();

        if(AIController == nullptr)
            return;

        APawn* AIPawn = AIController->GetPawn();

        float Distance = (OwnerComp.GetBlackboardComponent()->GetValueAsVector(TEXT("StartLocation")) - PlayerPawn->GetActorLocation()).Size();

        if(AIController->LineOfSightTo(PlayerPawn))
            OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("LineOfSight"),true);
        else{   
            OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("LineOfSight"));
        }

    }

    OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"),PlayerPawn->GetActorLocation());
    

}
