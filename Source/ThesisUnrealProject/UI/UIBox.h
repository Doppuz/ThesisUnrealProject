// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/SizeBox.h"
#include "UIBox.generated.h"

/**
 * 
 */
UCLASS()
class THESISUNREALPROJECT_API UUIBox : public UUserWidget
{
	GENERATED_BODY()
	

public:

	void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* NPCName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* DialogText;

	UPROPERTY(meta = (BindWidget))
	USizeBox* BoxContainer;

	UPROPERTY(meta = (BindWidget))
	class UBorder* BorderBox;


	void SetNPCName(FString Name);
	void SetDialogText(FString Dialog);
	void HideSizeBox();
	void ViewSizeBox();
};
