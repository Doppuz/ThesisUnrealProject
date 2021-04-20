// Copyright Epic Games, Inc. All Rights Reserved.


#include "CustomGameMode.h"
#include "CustomGameState.h"


ACustomGameMode::ACustomGameMode() {
    GameStateClass = ACustomGameState::StaticClass();
}

int ACustomGameMode::GetCoins() const{
    return GetGameState<ACustomGameState>()->CoinNumber;
}

void ACustomGameMode::IncreaseCoins() {
    GetGameState<ACustomGameState>()->CoinNumber += 1;
}

void ACustomGameMode::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass) {
    if (CurrentWidget != nullptr){
        CurrentWidget->RemoveFromViewport();
        CurrentWidget = nullptr;
    }
    if (NewWidgetClass != nullptr){
        CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
        if (CurrentWidget != nullptr){
            CurrentWidget->AddToViewport();
        }
    }
}

UUserWidget* ACustomGameMode::GetCurrentWidgetUI() {
    return CurrentWidget;
}

void ACustomGameMode::BeginPlay() {
    Super::BeginPlay();
    ChangeMenuWidget(StartingWidgetClass);
}

