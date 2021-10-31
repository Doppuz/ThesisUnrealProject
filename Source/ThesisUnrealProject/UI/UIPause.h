// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"	
#include "Components/Slider.h"
#include "UIPause.generated.h"

class UUIButton;

UCLASS()
class THESISUNREALPROJECT_API UUIPause : public UUserWidget{

	GENERATED_BODY()

public:

	void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UUIButton* ButtonResume;

	UPROPERTY(meta = (BindWidget))
	UUIButton* ButtonRestart;

	UPROPERTY(meta = (BindWidget))
	UUIButton* ButtonCommands;

	UPROPERTY(meta = (BindWidget))
	UUIButton* ButtonOptions;

	UPROPERTY(meta = (BindWidget))
	USlider* CameraSlider;

	UPROPERTY(meta = (BindWidget))
	UUIButton* ButtonBack;

	UPROPERTY(meta = (BindWidget))
	UUIButton* ButtonBack2;

	UPROPERTY(meta = (BindWidget))
	UUIButton* ButtonMenu;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* Switcher;

	
	
private:

	UFUNCTION()
	void OnResumeClicked();

	UFUNCTION()
	void OnRestart();

	UFUNCTION()
	void OnOptions();

	UFUNCTION()
	void OnBack();

	UFUNCTION()
	void OnCommands();

	UFUNCTION()
	void OnMenu();

	UFUNCTION()
	void OnValueChanged(float Value);

};
