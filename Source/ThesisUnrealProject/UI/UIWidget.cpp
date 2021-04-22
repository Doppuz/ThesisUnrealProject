// Fill out your copyright notice in the Description page of Project Settings.


#include "UIWidget.h"
#include "Components/TextBlock.h"

void UUIWidget::NativeConstruct() {
    
    Super::NativeConstruct();
    CoinsText->SetText(FText::Format(NSLOCTEXT("CoinsKey","CoinsSource", "{0}|plural(one=Coin,other=Coins) : {0}"), 0));
    MapText->SetText(FText::Format(NSLOCTEXT("CoinsKey","CoinsSource", "Map: {0} %"), 0));

}

void UUIWidget::SetCoinsText(int CoinAmount) {    
    CoinsText->SetText(FText::Format(NSLOCTEXT("CoinsKey","CoinsSource", "{0}|plural(one=Coin,other=Coins) : {0}"), CoinAmount));
}

void UUIWidget::SetMapText(float MapPercentage) {
    MapText->SetText(FText::Format(NSLOCTEXT("CoinsKey","CoinsSource", "Map: {0} %"), MapPercentage));
}
