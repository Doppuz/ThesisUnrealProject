// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AllyQuadAIController.generated.h"

/**
 * 
 */
UCLASS()
class THESISUNREALPROJECT_API AAllyQuadAIController : public AAIController{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BTree; 
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
