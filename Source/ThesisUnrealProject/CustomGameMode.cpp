// Copyright Epic Games, Inc. All Rights Reserved.


#include "CustomGameMode.h"
#include "CustomGameState.h"
#include "Graph/Graph.h"
#include "Containers/Array.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/GameplayStatics.h"
#include "UI/UIWidgetDialog.h"
#include "UI/Elements/UIBox.h"


ACustomGameMode::ACustomGameMode() {
    GameStateClass = ACustomGameState::StaticClass();
    NumberOfChest = 2;
    MapIncrement = 0;
}


ACustomGameMode::~ACustomGameMode() {

    //delete Populate;
}

void ACustomGameMode::BeginPlay() {
    Super::BeginPlay();

	UUIWidgetDialog* DialogWidget = Cast<UUIWidgetDialog>(CurrentWidget);
    DialogWidget->HideSizeBox();
    DialogWidget->TextBox->BoxContainer->Visibility = ESlateVisibility::Hidden;

}


//--- Get and Set for the coins and world percentage.

int ACustomGameMode::GetCoins() const{
    return GetGameState<ACustomGameState>()->CoinNumber;
}

void ACustomGameMode::IncreaseCoins() {
    GetGameState<ACustomGameState>()->CoinNumber += 1;
}

float ACustomGameMode::GetPercentage() const{
    return GetGameState<ACustomGameState>()->MapPercentage;
}

void ACustomGameMode::IncreasePercentage() {
    GetGameState<ACustomGameState>()->MapPercentage += MapIncrement;
}
