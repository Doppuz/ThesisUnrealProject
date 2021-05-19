// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTSetNextPosition.generated.h"

/**
 * 
 */
UCLASS()
class THESISUNREALPROJECT_API UBTSetNextPosition : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTSetNextPosition();

protected: 

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

	UPROPERTY(EditAnywhere)
	float Horizontal;

	UPROPERTY(EditAnywhere)
	float Vertical;
};
