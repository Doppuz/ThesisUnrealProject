// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OverlayedText.generated.h"

/**
 * Class used to create an overlay text over the actors.
 */
UCLASS()
class THESISUNREALPROJECT_API UOverlayedText : public UUserWidget{
	
	GENERATED_BODY()
	
public:
	
	UPROPERTY( meta = ( BindWidget ))
	class UTextBlock* OverlayedText;

	void SetText(FString);
	void SetColor(FLinearColor);

};
