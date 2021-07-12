// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../GameInstance/BartleManagerGameInstance.h"
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

	//Set the text in the dialog box
	TMap<int,TArray<FString>> MapDialogText;

	//Store the choice used for updating the Bartle Types.
	TMap<int,TArray<Type>> AnswerChoice;

	//Change UI
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> UIExplanation;
	
	int DialogTextContator = -1;

	void DialogInteraction(int , int );

	UFUNCTION()
	void OnButtonPlayClicked();
	
	UFUNCTION()
	void OnButtonQuitClicked();

	UFUNCTION()
	void Answer1Clicked();
	
	UFUNCTION()
	void Answer2Clicked();

};
