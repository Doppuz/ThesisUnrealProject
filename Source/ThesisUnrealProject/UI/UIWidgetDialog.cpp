// Fill out your copyright notice in the Description page of Project Settings.


#include "UIWidgetDialog.h"
#include "Components/TextBlock.h"
#include "UIBox.h"
#include "UserWidgetList.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"

void UUIWidgetDialog::NativeConstruct() {
    
    Super::NativeConstruct();
    HideAnswerBox();
    HidePopUp();
}

void UUIWidgetDialog::HideSizeBox() {
    TextBox->HideSizeBox();
}

void UUIWidgetDialog::ViewSizeBox() {
    TextBox->ViewSizeBox();
}

void UUIWidgetDialog::HideAnswerBox() {
    AnswerBox->HideListBox();
}

void UUIWidgetDialog::ViewAnswerBox() {
    AnswerBox->ViewListBox();
}

void UUIWidgetDialog::ViewPopUp() {
    PressPopUp->SetVisibility(ESlateVisibility::Visible);
}

void UUIWidgetDialog::HidePopUp() {
    PressPopUp->SetVisibility(ESlateVisibility::Hidden);
}

void UUIWidgetDialog::SetPopUpText(FString Text) {
    PopUpText->SetText(FText::FromString(Text));
}
