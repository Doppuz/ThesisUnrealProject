// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeAbstract.h"
#include "Kismet/GameplayStatics.h"
#include "CustomGameState.h"
#include "Character/CharacterPawnQuad.h"


AGameModeAbstract::AGameModeAbstract() {

	PrimaryActorTick.bCanEverTick = false;

    Update = new AdaptiveExperience();

	TotalCoins = 0;
    TotalEnemies = 0;
    TotalAllies = 0;
    TotalStatues = 0;

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

void AGameModeAbstract::StopGame(bool Enable){

    ACharacterPawnQuad* MyPawn = Cast<ACharacterPawnQuad>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
    MyPawn->SetMousePointer(Enable);

    APlayerController* Player = Cast<APlayerController>(MyPawn->GetController());
	if(Player != nullptr)
		Player->SetPause(Enable);

}

//--- Get and Set 

int AGameModeAbstract::GetCoins() const{
    return GetGameState<ACustomGameState>()->CoinsNumber;
}

void AGameModeAbstract::SetCoins(int Coins){
    GetGameState<ACustomGameState>()->CoinsNumber = Coins;
}

void AGameModeAbstract::IncreaseCoins() {
    GetGameState<ACustomGameState>()->CoinsNumber += 1;
}

int AGameModeAbstract::GetEnemies() const{
    return GetGameState<ACustomGameState>()->EnemiesDefeated;
}

void AGameModeAbstract::SetEnemies(int Enemies){
    GetGameState<ACustomGameState>()->EnemiesDefeated = Enemies;
}

void AGameModeAbstract::IncreaseEnemies() {
    GetGameState<ACustomGameState>()->EnemiesDefeated += 1;
}

int AGameModeAbstract::GetAllies() const{
    return GetGameState<ACustomGameState>()->AlliesSpoken;
}

void AGameModeAbstract::SetAllies(int Allies){
    GetGameState<ACustomGameState>()->AlliesSpoken = Allies;
}

void AGameModeAbstract::IncreaseAllies() {
    GetGameState<ACustomGameState>()->AlliesSpoken += 1;
}

int AGameModeAbstract::GetStatues() const{
    return GetGameState<ACustomGameState>()->StatueVisited;
}

void AGameModeAbstract::SetStatues(int Statues){
    GetGameState<ACustomGameState>()->StatueVisited = Statues;
}

void AGameModeAbstract::IncreaseStatues() {
    GetGameState<ACustomGameState>()->StatueVisited += 1;
}