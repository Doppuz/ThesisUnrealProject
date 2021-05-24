// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskShoot.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "QuadAIController.h"
#include "../Character/CharacterPawnQuad.h"

UBTTaskShoot::UBTTaskShoot() {
    NodeName = "Shoot";
}

EBTNodeResult::Type UBTTaskShoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory){
    
    Super::ExecuteTask(OwnerComp,NodeMemory);

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(OwnerComp.GetWorld(),0);
    AAIController* AIController = OwnerComp.GetAIOwner();

    if(AIController == nullptr)
        return EBTNodeResult::Failed;

    ACharacterPawnQuad* AIPawn = Cast<ACharacterPawnQuad>(AIController->GetPawn());
    AIPawn->Shoot();
    return EBTNodeResult::Succeeded;
}
