// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SetEnemiesInRange.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "../../Character/AllyAI/AICharacterPawnQuad.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"

UBTService_SetEnemiesInRange::UBTService_SetEnemiesInRange() {
    NodeName = "SetEnemiesInRange";
}

//It works only for AICharacterPawnQuad
void UBTService_SetEnemiesInRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
    
    Super::TickNode(OwnerComp,NodeMemory,DeltaSeconds);
    
    AAICharacterPawnQuad* AIPawn = Cast<AAICharacterPawnQuad>(OwnerComp.GetAIOwner()->GetPawn());

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);

    if(AIPawn->Enemies.Num() > 0){
        OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("CurrentEnemy"),AIPawn->Enemies[0]);
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("EnemyPosition"),AIPawn->Enemies[0]->GetActorLocation());

        FVector PlayerPosition = PlayerPawn->GetActorLocation() - PlayerPawn->GetActorForwardVector() * 200;

        if(FMath::RandRange(0,1) == 0)
            OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("AsidePosition"),PlayerPosition + PlayerPawn->GetActorRightVector() * 300);
        else
            OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("AsidePosition"),PlayerPosition + PlayerPawn->GetActorRightVector() * (-300));

    }else{
        FVector PlayerFollowPosition = OwnerComp.GetBlackboardComponent()->GetValueAsVector("PlayerFollowLocation");
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("EnemyPosition"),PlayerFollowPosition);
        OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("CurrentEnemy"));
        OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("AsidePosition"));
//        UE_LOG(LogTemp,Warning,TEXT("%s"),*OwnerComp.GetBlackboardComponent()->GetValueAsVector(TEXT("AsidePosition")).ToString());

        /*if(OwnerComp.GetBlackboardComponent()->Valid == true){
            UE_LOG(LogTemp,Warning,TEXT("true"));
        }else
            UE_LOG(LogTemp,Warning,TEXT("false"));*/
    }

    //OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"),PlayerPawn->GetActorLocation());
    

}
