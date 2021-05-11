// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeTutorial.h"
#include "Elements/PuzzleButton.h"
#include "Elements/Door.h"
#include "Kismet/GameplayStatics.h"

AGameModeTutorial::AGameModeTutorial() {
    bSolvedPuzzle1 = false;
    bGateDestroyed = false;
}

void AGameModeTutorial::BeginPlay() {
    TArray<AActor*> TempActors;
    UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(),DoorClass,TEXT("Puzzle1"),TempActors);
    if(TempActors.Num() > 0)
        DoorToOpen = Cast<ADoor>(TempActors[0]);
    else
        UE_LOG(LogTemp,Warning,TEXT("No door found."));
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
            DoorToOpen->bOpenDoor = true;
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
