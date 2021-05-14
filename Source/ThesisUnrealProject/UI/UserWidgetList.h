// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserWidgetList.h"
#include "UserWidgetList.generated.h"

class UUIAnswer;

/**
 * 
 */
UCLASS()
class THESISUNREALPROJECT_API UUserWidgetList : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnswerWidget")
    TSubclassOf<UUIAnswer> AnswerWidgetClass;
	
	UPROPERTY(meta = (BindWidget))
	class UListView* List;

	void AddElement();

	void ViewListBox();
	void HideListBox();
};
