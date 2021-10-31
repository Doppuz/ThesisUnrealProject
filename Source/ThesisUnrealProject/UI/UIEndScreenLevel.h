// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Elements/UserWidgetList.h"
#include "UIEndScreenLevel.generated.h"

/**
 * 
 */
UCLASS()
class THESISUNREALPROJECT_API UUIEndScreenLevel : public UUserWidget
{
	GENERATED_BODY()
	

public:

	void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UUIBox* TextBox;

	UPROPERTY(meta = (BindWidget))
	class UUIButton* Send;

	UPROPERTY(meta = (BindWidget))
	class UUIButton* Play;

	UPROPERTY(EditAnywhere)
	FName Level;

	UPROPERTY(EditAnywhere)
	FName Text;

	UPROPERTY(EditAnywhere)
	FName ButtonName;

// ---- Text ----

	void SetTestValue(float, float, float, float);
	void SetQuestionaryValue(float, float, float, float);

// ---- Buttons ----
	UFUNCTION()
	void OnSendClicked();
	
	UFUNCTION()
	void OnQuitClicked();

};
