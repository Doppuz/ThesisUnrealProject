// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_NewPosition.generated.h"

/**
 * 
 */
UCLASS()
class THESISUNREALPROJECT_API UBTService_NewPosition : public UBTService{

	GENERATED_BODY()
	
public:

	UBTService_NewPosition();

protected:

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
