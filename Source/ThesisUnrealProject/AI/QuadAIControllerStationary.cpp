// Fill out your copyright notice in the Description page of Project Settings.


#include "QuadAIControllerStationary.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackBoardComponent.h"

void AQuadAIControllerStationary::BeginPlay() {
    
    Super::BeginPlay();
    
    if(BTree != nullptr){
        RunBehaviorTree(BTree);
        APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"),GetPawn()->GetActorLocation());
    }else
        UE_LOG(LogTemp,Warning,TEXT("No Behavior Tree"));

}

void AQuadAIControllerStationary::Tick(float DeltaTime) {
    
    Super::Tick(DeltaTime);

    /*APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);

    if(BTree != nullptr){
        GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"),PlayerPawn->GetActorLocation());
    }
    
    /*APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);

    if(LineOfSightTo(PlayerPawn)){
        SetFocus(PlayerPawn);
        MoveToActor(PlayerPawn,200);
    }else{
        ClearFocus(EAIFocusPriority::Gameplay);
        StopMovement();
    }*/
}
