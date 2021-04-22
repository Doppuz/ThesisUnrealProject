// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UIWidget.generated.h"

/**
 * 
 */
UCLASS()
class THESISUNREALPROJECT_API UUIWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:

	void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CoinsText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MapText;

	void SetCoinsText(int CoinAmount);
	void SetMapText(float MapPercentage);
};
