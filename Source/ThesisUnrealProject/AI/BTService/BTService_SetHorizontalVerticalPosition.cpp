// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SetHorizontalVerticalPosition.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "../Controller/QuadAIController.h"

UBTService_SetHorizontalVerticalPosition::UBTService_SetHorizontalVerticalPosition() {
    NodeName = "SetNextPosition";
    Horizontal = 300.f;
    Vertical = 0.f;
}

void UBTService_SetHorizontalVerticalPosition::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {

    Super::TickNode(OwnerComp,NodeMemory,DeltaSeconds);

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
    AAIController* AIController = OwnerComp.GetAIOwner();

    if(AIController == nullptr)
        return;

    APawn* AIPawn = AIController->GetPawn();

    float Distance = (PlayerPawn->GetActorLocation() - AIPawn->GetActorLocation()).Size();

    FVector StartLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(TEXT("StartLocation"));
    
    float YValue = FMath::RandRange(-Horizontal,Horizontal);
    float XValue = FMath::RandRange(-Vertical,Vertical);

    OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("NextLocation"),StartLocation + FVector(XValue,YValue,0));

    /*if(PlayerPawn->GetActorLocation().Size() != (StartLocation + FVector(Horizontal,Vertical,0)).Size())
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("NextLocation"),StartLocation + FVector(Horizontal,Vertical,0));
    else{
        Horizontal = -Horizontal;
        Vertical = -Vertical;
    }*/


}
