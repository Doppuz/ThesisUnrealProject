// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UIAnswer.generated.h"

/**
 * 
 */
UCLASS()
class THESISUNREALPROJECT_API UUIAnswer : public UUserWidget
{
	GENERATED_BODY()
	
public: 

	void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Answer;

	void SetAnswerText();

	void ViewAnswerBox();
	void HideAnswerBox();

};
