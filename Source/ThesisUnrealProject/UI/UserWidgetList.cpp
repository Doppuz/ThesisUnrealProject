// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgetList.h"
#include "Components/ListView.h"
#include "UIAnswer.h"

void UUserWidgetList::NativeConstruct() {
    AddElement();
    HideListBox();
}

void UUserWidgetList::AddElement() {
    UUIAnswer* CurrentWidget = CreateWidget<UUIAnswer>(GetWorld(), AnswerWidgetClass);
    CurrentWidget->SetAnswerText();
    List->AddItem(CurrentWidget);
}

void UUserWidgetList::ViewListBox() {
    List->SetVisibility(ESlateVisibility::Visible);
}

void UUserWidgetList::HideListBox() {
    List->SetVisibility(ESlateVisibility::Hidden);
}
