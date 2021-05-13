// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SetRandomPosition.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "QuadAIController.h"

UBTService_SetRandomPosition::UBTService_SetRandomPosition() {
    NodeName = "SetRandomPosition";
}

void UBTService_SetRandomPosition::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
    AQuadAIController* AIController = Cast<AQuadAIController>(OwnerComp.GetAIOwner());

    if(AIController == nullptr)
        return;

    APawn* AIPawn = AIController->GetPawn();

    float Distance = (PlayerPawn->GetActorLocation() - AIPawn->GetActorLocation()).Size();

    if(!AIController->LineOfSightTo(PlayerPawn) || Distance > 1000.f){
        //AIController->ClearFocus(EAIFocusPriority::Gameplay);
        FVector StartLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(TEXT("StartLocation"));
        float AddingValueX = FMath::RandRange(-300,300);
        float AddingValueY = FMath::RandRange(-300,300);
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("RandomLocation"),StartLocation + FVector(AddingValueX,AddingValueY,0));
    }else{    
        //AIController->SetFocus(PlayerPawn);
        OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("RandomLocation"));
    }
}
