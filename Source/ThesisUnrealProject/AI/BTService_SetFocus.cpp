// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SetFocus.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "AIController.h"


UBTService_SetFocus::UBTService_SetFocus() {
    NodeName = "SetMyFocus";
}

void UBTService_SetFocus::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
    
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
    FVector PlayerPos = PlayerPawn->GetActorLocation();//OwnerComp.GetBlackboardComponent()->GetValueAsVector(TEXT("PlayerLocation"));
    AAIController* AIController = OwnerComp.GetAIOwner();

    if(AIController == nullptr)
        return;

    FVector AIPawnPos = AIController->GetPawn()->GetActorLocation();

    FVector NewPos = (AIPawnPos - PlayerPos);
    NewPos.Normalize();

	FVector NewLocation = FMath::Lerp(PlayerPos,NewPos, DeltaSeconds * 0.4f);
    //AIController->GetPawn()->SetActorRotation(NewLocation.Rotation());

    FRotator ActorRotator = AIController->GetPawn()->GetActorRotation();

    AIController->GetPawn()->SetActorRotation(FMath::RInterpTo(ActorRotator,NewPos.Rotation(),DeltaSeconds * 100,0.4));

}
