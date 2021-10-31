// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../GameModeTutorial.h"
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
	UUIButton* ButtonNewGame;

	UPROPERTY(meta = (BindWidget))
	UUIButton* ButtonContinue;
	
	UPROPERTY(meta = (BindWidget))
	UUIButton* ButtonTypes;
	
	UPROPERTY(meta = (BindWidget))
	UUIButton* ButtonCommands;

	UPROPERTY(meta = (BindWidget))
	UUIButton* ButtonQuit;
	
	UPROPERTY(meta = (BindWidget))
	UUIButton* ButtonBack;
	
	UPROPERTY(meta = (BindWidget))
	UUIButton* ButtonBack2;

	UPROPERTY(meta = (BindWidget))
	UUIButton* ButtonBack3;

	UPROPERTY(meta = (BindWidget))
	UUIButton* ButtonDelete;

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

	//Bartle's Texts
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CAchiever;
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CKiller;
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CExplorer;
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CSocializer;
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* OAchiever;
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* OKiller;
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* OExplorer;
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* OSocializer;

	UFUNCTION()
	void OnButtonPlayClicked();
	
	UFUNCTION()
	void OnButtonContinueClicked();
	
	UFUNCTION()
	void OnButtonQuitClicked();

	UFUNCTION()
	void Answer1Clicked();
	
	UFUNCTION()
	void Answer2Clicked();

	UFUNCTION()
	void OnBack();

	UFUNCTION()
	void OnTypes();
	
	UFUNCTION()
	void OnCommands();

	UFUNCTION()
	void OnDelete();

};
