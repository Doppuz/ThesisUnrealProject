// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GeneralElem.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NoCrateElements.generated.h"

UCLASS()
class THESISUNREALPROJECT_API ANoCrateElements : public AGeneralElem
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANoCrateElements();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAcces = true), Category = "DecorationElements")
	UStaticMeshComponent* MeshComponent4;
};
