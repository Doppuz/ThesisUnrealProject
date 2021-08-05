// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeAbstract.h"


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

    ChangeMenuWidget(StartingWidgetClass);

}