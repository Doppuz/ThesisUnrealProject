// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../Character/AllyAI/PawnInteractiveClass.h"
#include "StatueInteractElem.generated.h"


UCLASS()
class THESISUNREALPROJECT_API AStatueInteractElem : public APawnInteractiveClass{
	
	GENERATED_BODY()
	
public:

	AStatueInteractElem();

	static int ID;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
