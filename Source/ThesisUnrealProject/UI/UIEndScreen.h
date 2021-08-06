// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Elements/UserWidgetList.h"
#include "UIEndScreen.generated.h"

/**
 * 
 */
UCLASS()
class THESISUNREALPROJECT_API UUIEndScreen : public UUserWidget
{
	GENERATED_BODY()
	

public:

	void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UUIBox* TextBox;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Achiever;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Explorer;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Killer;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Socializer;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* AchieverQ;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ExplorerQ;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* KillerQ;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SocializerQ;

	UPROPERTY(meta = (BindWidget))
	class UUIButton* Send;

	UPROPERTY(meta = (BindWidget))
	UUIButton* Quit;

// ---- Text ----

	void SetTestValue(float, float, float, float);
	void SetQuestionaryValue(float, float, float, float);

// ---- Buttons ----
	UFUNCTION()
	void OnSendClicked();
	
	UFUNCTION()
	void OnQuitClicked();

};
