// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PatrolAIController.generated.h"

/**
 * 
 */
UCLASS()
class THESISUNREALPROJECT_API APatrolAIController : public AAIController{
	GENERATED_BODY()

public:

	APatrolAIController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BTree; 
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
