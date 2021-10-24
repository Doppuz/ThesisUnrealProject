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

    UGameplayStatics::GetPlayerController(GetWorld(),0)->SetInputMode(FInputModeGameOnly());

	UUIWidgetDialog* DialogWidget = Cast<UUIWidgetDialog>(CurrentWidget);
    DialogWidget->HideSizeBox();
    DialogWidget->TextBox->BoxContainer->Visibility = ESlateVisibility::Hidden;

}

void ACustomGameMode::StopGame(bool Enable){

    Super::StopGame(Enable);

}