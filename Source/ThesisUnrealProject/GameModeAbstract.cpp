// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeAbstract.h"
#include "CustomGameState.h"


AGameModeAbstract::AGameModeAbstract() {

	PrimaryActorTick.bCanEverTick = false;

    Update = new AdaptiveExperience();

}

AGameModeAbstract::~AGameModeAbstract() {
    delete Update;
}


//Assign the UI widget passed as parameter to the screen.
void AGameModeAbstract::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass) {
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

//Get current UI
UUserWidget* AGameModeAbstract::GetCurrentWidgetUI() {
    return CurrentWidget;
}

void AGameModeAbstract::BeginPlay() {
    
    Super::BeginPlay();

    LoadedLevels.Add("Day");

    ChangeMenuWidget(StartingWidgetClass);

}


//--- Get and Set for the coins and world percentage.

int AGameModeAbstract::GetCoins() const{
    return GetGameState<ACustomGameState>()->CoinsNumber;
}

void AGameModeAbstract::IncreaseCoins() {
    GetGameState<ACustomGameState>()->CoinsNumber += 1;
}

int AGameModeAbstract::GetEnemies() const{
    return GetGameState<ACustomGameState>()->EnemiesDefeated;
}

void AGameModeAbstract::IncreaseEnemies() {
    GetGameState<ACustomGameState>()->EnemiesDefeated += 1;
}

int AGameModeAbstract::GetAllies() const{
    return GetGameState<ACustomGameState>()->AlliesSpoken;
}

void AGameModeAbstract::IncreaseAllies() {
    GetGameState<ACustomGameState>()->AlliesSpoken += 1;
}

int AGameModeAbstract::GetStatues() const{
    return GetGameState<ACustomGameState>()->StatueVisited;
}

void AGameModeAbstract::IncreaseStatues() {
    GetGameState<ACustomGameState>()->StatueVisited += 1;
}