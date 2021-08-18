// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskShoot.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "../Controller/QuadAIController.h"
#include "../../Character/EnemyAI/AIShooterPawn.h"

UBTTaskShoot::UBTTaskShoot() {
    NodeName = "Shoot";
}

EBTNodeResult::Type UBTTaskShoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory){
    
    Super::ExecuteTask(OwnerComp,NodeMemory);

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(OwnerComp.GetWorld(),0);
    AAIController* AIController = OwnerComp.GetAIOwner();

    if(AIController == nullptr)
        return EBTNodeResult::Failed;

    AAIShooterPawn* AIPawn = Cast<AAIShooterPawn>(AIController->GetPawn());
    AIPawn->Shoot();
    return EBTNodeResult::Succeeded;
}
