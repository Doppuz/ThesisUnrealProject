// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UIButton.generated.h"

/**
 * 
 */
UCLASS()
class THESISUNREALPROJECT_API UUIButton : public UUserWidget
{
	GENERATED_BODY()
	

public:

	void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UButton* ButtonPlay;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text;

};
