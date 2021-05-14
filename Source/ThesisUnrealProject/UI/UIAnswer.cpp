// Fill out your copyright notice in the Description page of Project Settings.


#include "UIAnswer.h"
#include "Components/TextBlock.h"

void UUIAnswer::NativeConstruct() {
    Super::NativeConstruct();
}

void UUIAnswer::SetAnswerText() {
    Answer->SetText(FText::FromString("Can you see your text?"));
}

void UUIAnswer::ViewAnswerBox() {
    Answer->SetVisibility(ESlateVisibility::Hidden);
}

void UUIAnswer::HideAnswerBox() {
    Answer->SetVisibility(ESlateVisibility::Visible);
}
