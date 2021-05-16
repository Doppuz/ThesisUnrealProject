// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTaskEquipment.generated.h"

/**
 * 
 */
UCLASS()
class THESISUNREALPROJECT_API UBTTaskEquipment : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTaskEquipment();

protected: 

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
