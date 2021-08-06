// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "QuadAIBull.generated.h"

/**
 * 
 */
UCLASS()
class THESISUNREALPROJECT_API AQuadAIBull : public AAIController
{
	GENERATED_BODY()

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BTree; 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
