// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeAbstract.h"
#include "Kismet/GameplayStatics.h"
#include "CustomGameState.h"
#include "Character/CharacterPawnQuad.h"
#include "UI/UIWidgetDialog.h"
#include "UI/Elements/UIBox.h"


AGameModeAbstract::AGameModeAbstract() {

	PrimaryActorTick.bCanEverTick = false;

    Update = new AdaptiveExperience();

	TotalCoins = 0;
    TotalEnemies = 0;
    TotalAllies = 0;
    TotalMap = 0;

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

Type AGameModeAbstract::ReturnBartleHighest(){

    TMap<Type,float> Types = Update->Types;

    Types.ValueSort([] (float A, float B){
        return A > B;
    } );

    TArray<Type> Keys;
    Types.GetKeys(Keys);

    return Keys[0];

}

void AGameModeAbstract::SetPause(bool Enable){

    StopGame(Enable);

    if(Enable)
        ChangeMenuWidget(PauseWidget);
    else{
        ChangeMenuWidget(StartingWidgetClass);
        UUIWidgetDialog* DialogWidget = Cast<UUIWidgetDialog>(CurrentWidget);
        DialogWidget->HideSizeBox();
        DialogWidget->TextBox->BoxContainer->Visibility = ESlateVisibility::Hidden;
    }
    
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
    UE_LOG(LogTemp,Warning,TEXT("Coins = %i / %i"),GetCoins(),TotalCoins);

}

int AGameModeAbstract::GetEnemies() const{
    return GetGameState<ACustomGameState>()->EnemiesDefeated;
}

void AGameModeAbstract::SetEnemies(int Enemies){
    GetGameState<ACustomGameState>()->EnemiesDefeated = Enemies;
}

void AGameModeAbstract::IncreaseEnemies() {

    GetGameState<ACustomGameState>()->EnemiesDefeated += 1;
    UE_LOG(LogTemp,Warning,TEXT("Enemies = %i / %i"),GetEnemies(),TotalEnemies);

}

int AGameModeAbstract::GetAllies() const{
    return GetGameState<ACustomGameState>()->AlliesSpoken;
}

void AGameModeAbstract::SetAllies(int Allies){
    GetGameState<ACustomGameState>()->AlliesSpoken = Allies;
}

void AGameModeAbstract::IncreaseAllies() {

    GetGameState<ACustomGameState>()->AlliesSpoken += 1;
    UE_LOG(LogTemp,Warning,TEXT("Allies = %i / %i"),GetAllies(),TotalAllies);

}

int AGameModeAbstract::GetMap() const{
    return GetGameState<ACustomGameState>()->MapVisited;
}

void AGameModeAbstract::SetMap(int Map){
    GetGameState<ACustomGameState>()->MapVisited = Map;
}

void AGameModeAbstract::IncreaseMap() {

    GetGameState<ACustomGameState>()->MapVisited += 1;
    UE_LOG(LogTemp,Warning,TEXT("Map = %i / %i"),GetMap(),TotalMap);

}