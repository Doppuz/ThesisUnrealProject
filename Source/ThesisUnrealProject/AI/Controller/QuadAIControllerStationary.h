// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "QuadAIControllerStationary.generated.h"

/**
 * 
 */
UCLASS()
class THESISUNREALPROJECT_API AQuadAIControllerStationary : public AAIController
{
	GENERATED_BODY()

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BTree; 

	//Horizontal movement value changed on the trigger class.
	float MovementValue;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	//AI Timer movement
	FTimerHandle MovementTimer;
	void Movement();

	UPROPERTY(EditAnywhere)
	bool bStationary = true;
};
