// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UIMainMenu.generated.h"

class UUIButton;

/**
 * 
 */
UCLASS()
class THESISUNREALPROJECT_API UUIMainMenu : public UUserWidget
{
	GENERATED_BODY()
	

public:

	void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UUIButton* ButtonPlay;

	UPROPERTY(meta = (BindWidget))
	UUIButton* ButtonQuit;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* Switcher;
	
	UPROPERTY(meta = (BindWidget))
	class UUIBox* TextBox;

	UPROPERTY(meta = (BindWidget))
	class UUIAnswer* Answer1;
	
	UPROPERTY(meta = (BindWidget))
	UUIAnswer* Answer2;

	UPROPERTY(meta = (BindWidget))
	class USizeBox* PopUp;

	TMap<int,TArray<FString>> MapDialogText;

	UFUNCTION()
	void OnButtonPlayClicked();
	
	UFUNCTION()
	void OnButtonQuitClicked();
	
};
