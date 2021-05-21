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
    ChangeMenuWidget(WidgetClass);
	UUIWidgetDialog* DialogWidget = Cast<UUIWidgetDialog>(CurrentWidget);
    DialogWidget->HideSizeBox();
    DialogWidget->TextBox->BoxContainer->Visibility = ESlateVisibility::Hidden;
}

void AGameModeTutorial::Tick(float DeltaTime) {
    
}

//Check if all of the 3 buttuns has been clicked. If yes check if the combination is correct.
void AGameModeTutorial::CheckPuzzle1(APuzzleButton* Button) {
    
    ElemsPuzzle1.Add(Button);

    if(ElemsPuzzle1.Num() == 3){
        
        bool TempResult = true;
        for(int i = 0; i < ElemsPuzzle1.Num(); i++)
            TempResult &= ElemsPuzzle1[i]->GetID() == i;

        bSolvedPuzzle1 = TempResult; 

        if(bSolvedPuzzle1){
            for(APuzzleButton* Butt : ElemsPuzzle1)
                Butt->Mesh->SetMaterial(0,GreenColor);

                ADoor* DoorToOpen;
                for(int i = 0; i < 2; i++){
                    DoorToOpen = Cast<ADoor>(DoorActors[i]);
                    DoorToOpen->bOpenDoor = true;
                }
            
        }else{
            for(APuzzleButton* Butt : ElemsPuzzle1)
                Butt->Mesh->SetMaterial(0,RedColor);
            GetWorld()->GetTimerManager().SetTimer(ResetPuzzle1Timer,this,&AGameModeTutorial::ResetPuzzle1,0.5f,false);
        }

    }
}

void AGameModeTutorial::ResetPuzzle1() {

    for(APuzzleButton* Butt : ElemsPuzzle1){
        Butt->Mesh->SetMaterial(0,GreyColor);
        Butt->bDisableOverlap = false;
    }
    bSolvedPuzzle1 = true;
    ElemsPuzzle1.Empty();
}

//Check if I spoke or killed all the actor in one of the two rooms.
void AGameModeTutorial::CheckPuzzle2(int ID) {
    if(bLeft){
        if(!ElemsPuzzle2.Contains(ID)){
            ElemsPuzzle2.Add(ID);
            if(ElemsPuzzle2.Num() == 2){
                Cast<ADoor>(DoorActors[7])->bOpenDoor = true;
            }
        }
    }else{
        if(!ElemsPuzzle2.Contains(ID)){
            ElemsPuzzle2.Add(ID);
            if(ElemsPuzzle2.Num() == 3){
                Cast<ADoor>(DoorActors[7])->bOpenDoor = true;
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

//--- Get and Set for the coins

int AGameModeTutorial::GetCoins() const{
    return GetGameState<ACustomGameState>()->CoinNumber;
}

void AGameModeTutorial::IncreaseCoins() {
    GetGameState<ACustomGameState>()->CoinNumber += 1;
}
