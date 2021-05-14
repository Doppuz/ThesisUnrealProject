// Fill out your copyright notice in the Description page of Project Settings.


#include "UIBox.h"
#include "Components/TextBlock.h"
#include "Components/SizeBox.h"

void UUIBox::NativeConstruct() {
    
    Super::NativeConstruct();
    NPCName->SetText(FText::FromString("NPC"));
    DialogText->SetText(FText::FromString("Can you see your text?"));

}

void UUIBox::SetNPCName(FString Name) {    
    NPCName->SetText(FText::FromString("Can you see your text?"));
}

void UUIBox::SetDialogText(FString Dialog) {
    DialogText->SetText(FText::FromString("Can you see your text?"));
}

void UUIBox::HideSizeBox() {
    BoxContainer->SetVisibility(ESlateVisibility::Hidden);
}

void UUIBox::ViewSizeBox() {
    BoxContainer->SetVisibility(ESlateVisibility::Visible);
}