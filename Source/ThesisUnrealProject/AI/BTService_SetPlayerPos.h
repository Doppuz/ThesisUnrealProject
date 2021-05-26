// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_SetPlayerPos.generated.h"

/**
 * 
 */
UCLASS()
class THESISUNREALPROJECT_API UBTService_SetPlayerPos : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_SetPlayerPos();

	UPROPERTY(EditAnywhere)
	bool bRange;

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
