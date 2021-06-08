// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SetPlayerFollowPos.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "../Character/CharacterPawnQuad.h"

UBTService_SetPlayerFollowPos::UBTService_SetPlayerFollowPos() {
    NodeName = "SetPlayerPosition";
}

void UBTService_SetPlayerFollowPos::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {

    ACharacterPawnQuad* PlayerPawn = Cast<ACharacterPawnQuad>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
    OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerFollowLocation"),PlayerPawn->FollowAllyPosition->GetComponentLocation());
    
}
