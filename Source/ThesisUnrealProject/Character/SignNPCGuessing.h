// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnInteractiveClass.h"
#include "SignNPCGuessing.generated.h"

class ADoor;

/**
 * 
 */
UCLASS()
class THESISUNREALPROJECT_API ASignNPCGuessing : public APawnInteractiveClass
{
	GENERATED_BODY()

public:

	ASignNPCGuessing();

	virtual void Choice(int Answer) override;

	virtual void Ask() override;

};
