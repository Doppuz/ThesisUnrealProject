// Fill out your copyright notice in the Description page of Project Settings.


#include "UIWidgetDialog.h"
#include "Components/TextBlock.h"
#include "UIBox.h"
#include "UserWidgetList.h"

void UUIWidgetDialog::NativeConstruct() {
    
    Super::NativeConstruct();
    HideAnswerBox();
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
