// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_SetHorizontalVerticalPosition.generated.h"

/**
 * 
 */
UCLASS()
class THESISUNREALPROJECT_API UBTService_SetHorizontalVerticalPosition : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_SetHorizontalVerticalPosition();

protected:

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere)
	float Horizontal;

	UPROPERTY(EditAnywhere)
	float Vertical;
};
