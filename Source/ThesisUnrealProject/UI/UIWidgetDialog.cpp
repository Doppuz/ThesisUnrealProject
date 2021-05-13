// Fill out your copyright notice in the Description page of Project Settings.


#include "UIWidgetDialog.h"
#include "Components/TextBlock.h"

void UUIWidgetDialog::NativeConstruct() {
    
    Super::NativeConstruct();
    DialogText->SetText(FText::FromString("Can you see your text?"));

}

void UUIWidgetDialog::SetDialogText(int CoinAmount) {    
    DialogText->SetText(FText::FromString("Can you see your text?"));
}
