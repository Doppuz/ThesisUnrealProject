// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.h"
#include "DoorOrderPuzzle.generated.h"

class APuzzleButton;

UCLASS()
class THESISUNREALPROJECT_API ADoorOrderPuzzle : public ADoor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoorOrderPuzzle();

protected:

	//check if the door can be opened. It works only for buttons.
	virtual void CheckActorOverlap() override;

	UPROPERTY(EditAnywhere, Category = "Opening")
	TArray<APuzzleButton*> RightOrder;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = "true"), Category = Materials)
	UMaterial* GreenColor;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = "true"), Category = Materials)
	UMaterial* RedColor;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = "true"), Category = Materials)
	UMaterial* GreyColor;

	//Used to reset the color of the buttons
	void ResetPuzzle();

	//Timers
	FTimerHandle ResetPuzzleTimer;
};
