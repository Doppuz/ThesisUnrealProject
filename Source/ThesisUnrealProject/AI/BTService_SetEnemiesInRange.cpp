// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SetEnemiesInRange.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "../Character/AICharacterPawnQuad.h"
#include "AIController.h"

UBTService_SetEnemiesInRange::UBTService_SetEnemiesInRange() {
    NodeName = "SetEnemiesInRange";
}

//It works only for AICharacterPawnQuad
void UBTService_SetEnemiesInRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {

    AAICharacterPawnQuad* AIPawn = Cast<AAICharacterPawnQuad>(OwnerComp.GetAIOwner()->GetPawn());

    if(AIPawn->Enemies.Num() > 0){
        OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("CurrentEnemy"),AIPawn->Enemies[0]);
    }else
        OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("CurrentEnemy"));

    //OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"),PlayerPawn->GetActorLocation());
    

}
