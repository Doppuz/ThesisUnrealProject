// Fill out your copyright notice in the Description page of Project Settings.


#include "UIAnswer.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UUIAnswer::NativeConstruct() {
    Super::NativeConstruct();
}

void UUIAnswer::SetAnswerText(FString Text) {
    Answer->SetText(FText::FromString(Text));
}

void UUIAnswer::ViewAnswerBox() {
    Answer->SetVisibility(ESlateVisibility::Hidden);
}

void UUIAnswer::HideAnswerBox() {
    Answer->SetVisibility(ESlateVisibility::Visible);
}