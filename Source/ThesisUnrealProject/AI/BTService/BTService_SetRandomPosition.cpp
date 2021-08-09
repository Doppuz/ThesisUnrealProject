// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SetRandomPosition.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "../Controller/QuadAIController.h"
#include "../../Character/CharacterPawnQuad.h"

UBTService_SetRandomPosition::UBTService_SetRandomPosition() {
    NodeName = "SetRandomPosition";
    ShootRange = 1000.f;
    RandomDistance = 300.f;
}

void UBTService_SetRandomPosition::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
 
    Super::TickNode(OwnerComp,NodeMemory,DeltaSeconds);
    
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
    AAIController* AIController = OwnerComp.GetAIOwner();

    if(AIController == nullptr)
        return;

    APawn* AIPawn = AIController->GetPawn();

    float Distance = (PlayerPawn->GetActorLocation() - AIPawn->GetActorLocation()).Size();

    if(!AIController->LineOfSightTo(PlayerPawn) || Distance > ShootRange){ //1000
        //AIController->ClearFocus(EAIFocusPriority::Gameplay);
        FVector StartLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(TEXT("StartLocation"));
        float AddingValueX = FMath::RandRange(-RandomDistance,RandomDistance);
        float AddingValueY = FMath::RandRange(-RandomDistance,RandomDistance);
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("RandomLocation"),StartLocation + FVector(AddingValueX,AddingValueY,0));
    }else{    
        //AIController->SetFocus(PlayerPawn);
        OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("RandomLocation"));
    }
}
