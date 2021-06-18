// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeTutorial.h"
#include "Elements/PuzzleButton.h"
#include "Elements/Door.h"
#include "Kismet/GameplayStatics.h"
#include "UI/UIWidgetDialog.h"
#include "UI/UIBox.h"
#include "CustomGameState.h"
#include "Engine/TriggerVolume.h"

AGameModeTutorial::AGameModeTutorial() {
    bSolvedPuzzle1 = false;
    bGateDestroyed = false;
    bEnemyDefeated = false;
}

void AGameModeTutorial::BeginPlay() {

    FLatentActionInfo LatentInfo;
	UGameplayStatics::LoadStreamLevel(this, TEXT("Day"), true, true, LatentInfo);

    UGameplayStatics::GetAllActorsOfClass(GetWorld(),DoorClass,DoorActors);
    ChangeMenuWidget(WidgetClass);
	UUIWidgetDialog* DialogWidget = Cast<UUIWidgetDialog>(CurrentWidget);
    DialogWidget->HideSizeBox();
    DialogWidget->TextBox->BoxContainer->Visibility = ESlateVisibility::Hidden;
}

void AGameModeTutorial::Tick(float DeltaTime) {
    
}

//Check if I spoke or killed all the actor in one of the two rooms.
void AGameModeTutorial::CheckPuzzle2(int ID) {
	AGameModeTutorial* GameMode = Cast<AGameModeTutorial>(GetWorld()->GetAuthGameMode());
    if(bLeft){
        if(!ElemsPuzzle2.Contains(ID)){
            ElemsPuzzle2.Add(ID);
            if(ElemsPuzzle2.Num() == 2){
                GameMode->SetDoorOpen(7);
            }
        }
    }else{
        if(!ElemsPuzzle2.Contains(ID)){
            ElemsPuzzle2.Add(ID);
            if(ElemsPuzzle2.Num() == 3){
                GameMode->SetDoorOpen(7);
            }
        }
    }
}

//Assign the UI widget passed as parameter to the screen.
void AGameModeTutorial::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass) {
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
UUserWidget* AGameModeTutorial::GetCurrentWidgetUI() {
    return CurrentWidget;
}

void AGameModeTutorial::SetDoorOpen(int DoorNum) {
    for(AActor* Door: DoorActors){
        ADoor* CastDoor = Cast<ADoor>(Door);
        if(CastDoor->ID == DoorNum)
            CastDoor->bOpenDoor = true;
    }
}

//--- Get and Set for the coins

int AGameModeTutorial::GetCoins() const{
    return GetGameState<ACustomGameState>()->CoinNumber;
}

void AGameModeTutorial::IncreaseCoins() {
    GetGameState<ACustomGameState>()->CoinNumber += 1;
}
