// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SetPlayerPos.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "../Character/CharacterController.h"
#include "AIController.h"


UBTService_SetPlayerPos::UBTService_SetPlayerPos() {
    NodeName = "SetPlayerPosition";
    bRange = false;
}

void UBTService_SetPlayerPos::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
    
    //If I activate the bRange bool, I set the value of the PlayerLocation only if I the AI see me and within a specific range. 
    //If not I just set the value of the PlayerLocation
    if(bRange){

        AAIController* AIController = OwnerComp.GetAIOwner();

        if(AIController == nullptr)
            return;

        APawn* AIPawn = AIController->GetPawn();

        float Distance = (OwnerComp.GetBlackboardComponent()->GetValueAsVector(TEXT("StartLocation")) - PlayerPawn->GetActorLocation()).Size();
                UE_LOG(LogTemp,Warning,TEXT("%f"),Distance);

        if(Distance < 700.f)
            OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"),PlayerPawn->GetActorLocation());
        else{   
            OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
        }

    }else
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"),PlayerPawn->GetActorLocation());
    

}
