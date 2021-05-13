// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SetPlayerPos.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackBoardComponent.h"


UBTService_SetPlayerPos::UBTService_SetPlayerPos() {
    NodeName = "SetPlayerPosition";
}

void UBTService_SetPlayerPos::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
    
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
    OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"),PlayerPawn->GetActorLocation());
}
