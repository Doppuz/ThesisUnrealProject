// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeTutorial.h"
#include "Elements/PuzzleButton.h"
#include "Elements/Door.h"
#include "Kismet/GameplayStatics.h"
#include "UI/UIWidgetDialog.h"
#include "UI/UIBox.h"

AGameModeTutorial::AGameModeTutorial() {
    bSolvedPuzzle1 = false;
    bGateDestroyed = false;
}

void AGameModeTutorial::BeginPlay() {
    UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(),DoorClass,TEXT("Puzzle1"),DoorActors);
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

            for(AActor* Door : DoorActors){
                ADoor* DoorToOpen = Cast<ADoor>(Door);
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
