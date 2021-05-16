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

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnswerWidget")
    //TSubclassOf<UUIAnswer> AnswerWidgetClass;
	
	//UPROPERTY(meta = (BindWidget))
	//class UListView* List;

	UPROPERTY(meta = (BindWidget))
	UUIAnswer* Answer1;
	
	UPROPERTY(meta = (BindWidget))
	UUIAnswer* Answer2;

	//TArray<UUIAnswer*> AnswerList;

	//void AddElement();

	//Change the value of the text in the answers.
	//void SetText(TArray<FString>);
	//void ResetList();

	void SetAnswer1(FString);
	void SetAnswer2(FString);

	UFUNCTION()
	void OnButton1Clicked();
	
	UFUNCTION()
	void OnButton2Clicked();

	void ViewListBox();
	void HideListBox();
};
