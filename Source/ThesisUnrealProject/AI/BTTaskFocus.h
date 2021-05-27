// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskFocus.generated.h"

/**
 * 
 */
UCLASS()
class THESISUNREALPROJECT_API UBTTaskFocus : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTaskFocus();

	UPROPERTY(EditAnywhere)
	bool bFocus;

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


};
