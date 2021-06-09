// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_CheckLineOfSight.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "QuadAIController.h"
#include "../Character/AICharacterPawnQuad.h"
#include "../Character/EnemyAIAbstract.h"
#include "Kismet/KismetSystemLibrary.h"

UBTService_CheckLineOfSight::UBTService_CheckLineOfSight() {
    NodeName = "LineOfSight";
}

void UBTService_CheckLineOfSight::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
    AAIController* AIController = OwnerComp.GetAIOwner();

    if(AIController == nullptr)
        return;

    //float Distance = (PlayerPawn->GetActorLocation() - AIPawn->GetActorLocation()).Size();

    //float RandomDistance = Cast<ACharacterPawnQuad>(AIPawn)->MaxRandomDistance;
    
    FVector End = AIController->GetPawn()->GetActorLocation() + AIController->GetPawn()->GetActorRotation().Vector() * 1000;

	FCollisionQueryParams Params(NAME_None, true, AIController->GetPawn());

    TArray<AActor*> IgnoredActors;

    IgnoredActors.Add(AIController->GetPawn());

    FHitResult Hit;

    UKismetSystemLibrary::BoxTraceSingle(GetWorld(),AIController->GetPawn()->GetActorLocation(), End,FVector(16.f,16.f,16.f),
        AIController->GetPawn()->GetActorRotation(), UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_GameTraceChannel7),
        true, IgnoredActors, EDrawDebugTrace::Persistent,Hit,true);

    AEnemyAIAbstract* Enemy = Cast<AEnemyAIAbstract>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("CurrentEnemy"));

    if(Hit.GetActor() != nullptr && Enemy != nullptr && Hit.GetActor() == Enemy){// || Distance > 1000.f){ //1000
        OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("CanISeeTheEnemy"),true);
    }else
        OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("CanISeeTheEnemy"));
    
}
