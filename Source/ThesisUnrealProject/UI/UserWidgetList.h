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

	UPROPERTY(meta = (BindWidget))
	UUIAnswer* Answer3;
	
	UPROPERTY(meta = (BindWidget))
	UUIAnswer* Answer4;

	//TArray<UUIAnswer*> AnswerList;

	//void AddElement();

	//Change the value of the text in the answers.
	//void SetText(TArray<FString>);
	//void ResetList();

	void SetAnswer1(FString);
	void SetAnswer2(FString);
	void SetAnswer3(FString);
	void SetAnswer4(FString);

	UFUNCTION()
	void OnButton1Clicked();
	
	UFUNCTION()
	void OnButton2Clicked();
	
	UFUNCTION()
	void OnButton3Clicked();
	
	UFUNCTION()
	void OnButton4Clicked();

	void ViewListBox();
	void HideListBox();
	void ViewListBoxGuessing();
};
