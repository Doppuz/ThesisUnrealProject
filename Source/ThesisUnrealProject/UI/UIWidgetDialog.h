// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UIWidgetDialog.generated.h"

/**
 * 
 */
UCLASS()
class THESISUNREALPROJECT_API UUIWidgetDialog : public UUserWidget
{
	GENERATED_BODY()
	

public:

	void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* DialogText;

	void SetDialogText(int CoinAmount);
};
