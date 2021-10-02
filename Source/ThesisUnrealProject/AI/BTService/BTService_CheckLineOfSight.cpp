// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_CheckLineOfSight.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "../Controller/QuadAIController.h"
#include "../../Character/AllyAI/AICharacterPawnQuad.h"
#include "../../Character/EnemyAI/EnemyAIAbstract.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"

UBTService_CheckLineOfSight::UBTService_CheckLineOfSight() {
    NodeName = "LineOfSight";
}

void UBTService_CheckLineOfSight::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {

    Super::TickNode(OwnerComp,NodeMemory,DeltaSeconds);
    
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
    AAIController* AIController = OwnerComp.GetAIOwner();

    if(AIController == nullptr)
        return;
    
    //Line tracing

    FVector End = AIController->GetPawn()->GetActorLocation() + AIController->GetPawn()->GetActorRotation().Vector() * 1500;

	FCollisionQueryParams Params(NAME_None, true, AIController->GetPawn());

    TArray<AActor*> IgnoredActors;

    IgnoredActors.Add(AIController->GetPawn());

    FHitResult Hit;

    GetWorld()->LineTraceSingleByChannel(Hit,AIController->GetPawn()->GetActorLocation(),End,ECollisionChannel::ECC_GameTraceChannel7,
        Params);

    AEnemyAIAbstract* Enemy = Cast<AEnemyAIAbstract>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("CurrentEnemy"));

    TArray<AActor*> Enemies = Cast<AAICharacterPawnQuad>(AIController->GetPawn())->Enemies;

    //Check the result

    if(Hit.GetActor() != nullptr && Enemy != nullptr && Enemies.Contains(Hit.GetActor())){// || Distance > 1000.f){ //1000
        OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("CanISeeTheEnemy"),true);
    }else
        OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("CanISeeTheEnemy"));
    
}
