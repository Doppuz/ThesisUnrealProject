// Fill out your copyright notice in the Description page of Project Settings.


#include "AllyQuadAIController.h"
#include "BehaviorTree/BlackBoardComponent.h"


void AAllyQuadAIController::BeginPlay() {
    
    Super::BeginPlay();
    
    if(BTree != nullptr){
        RunBehaviorTree(BTree);
        //APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
        GetBlackboardComponent()->SetValueAsString(TEXT("SpeakText"),TEXT("22"));
    }else
        UE_LOG(LogTemp,Warning,TEXT("No Behavior Tree"));
    
}
