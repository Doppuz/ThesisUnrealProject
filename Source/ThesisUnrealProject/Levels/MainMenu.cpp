// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "kismet/GameplayStatics.h"


void AMainMenu::BeginPlay() {
    
    Super::BeginPlay();

    ChangeMenuWidget(WidgetClass);

    UGameplayStatics::GetPlayerController(GetWorld(),0)->SetInputMode(FInputModeUIOnly());
    UGameplayStatics::GetPlayerController(GetWorld(),0)->SetShowMouseCursor(true);

}

void AMainMenu::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass) {
    
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
