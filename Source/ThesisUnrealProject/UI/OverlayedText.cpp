// Fill out your copyright notice in the Description page of Project Settings.


#include "OverlayedText.h"
#include "Components/TextBlock.h"

void UOverlayedText::SetText(FString NewText) {
    
    OverlayedText->SetText(FText::FromString(NewText));

}

void UOverlayedText::SetColor(FLinearColor Color) {
    
    OverlayedText->SetColorAndOpacity(Color);

}
