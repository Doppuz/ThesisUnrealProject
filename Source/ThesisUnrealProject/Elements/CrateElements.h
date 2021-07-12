// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GeneralElem.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CrateElements.generated.h"

UCLASS()
class THESISUNREALPROJECT_API ACrateElements : public AGeneralElem
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACrateElements();
	
	bool IAmDestructed;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAcces = true), Category = "Destruction")
	class UDestructibleComponent* DestructibleComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:


	UFUNCTION()
	void OnComponentFracture(const FVector& HitPoint, const FVector& HitDirection);
};
