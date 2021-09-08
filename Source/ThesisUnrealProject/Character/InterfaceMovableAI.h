// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EnemyAI/EnemyAIAbstract.h"
#include "InterfaceMovableAI.generated.h"


//Class for the creation of an AI that move from point A to B.
UINTERFACE(MinimalAPI, Blueprintable)
class UInterfaceMovableAI : public UInterface{

	GENERATED_BODY()

};

class THESISUNREALPROJECT_API IInterfaceMovableAI{

    GENERATED_BODY()

public:

	TArray<FVector> Positions;

	virtual void SetInitialValue(FVector, int, bool);

};
