// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnInteractiveClass.h"
#include "RiddleNPC.generated.h"

class ADoor;

/**
 * 
 */
UCLASS()
class THESISUNREALPROJECT_API ARiddleNPC : public APawnInteractiveClass
{
	GENERATED_BODY()

public:

	ARiddleNPC();

	virtual void Choice(int Answer) override;
	
	virtual void Ask() override;

	UPROPERTY(EditAnywhere, Category = "Speak")
	int RightAnswerPos;

};
