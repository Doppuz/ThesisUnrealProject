// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorOrderPuzzle.h"
#include "Components/BoxComponent.h"
#include "PuzzleButton.h"
#include "../GameModeTutorial.h"

// Sets default values
ADoorOrderPuzzle::ADoorOrderPuzzle(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

//It works only for buttons.
void ADoorOrderPuzzle::CheckPuzzleActor() {

	AGameModeTutorial* GameMode = Cast<AGameModeTutorial>(GetWorld()->GetAuthGameMode());

	if(ComplementaryActor != nullptr && ComplementaryActor->bSolved)
		return;

	//In this case the condition is not used.
	if(PuzzleActivator.Num() == 0)
		return;

	//Add to the right actor vector if boverlap is false.
	if(PuzzleActivator.Num() != GameMode->ElemsPuzzle.Num()){
		return;
	}

	for(int i = 0; i < PuzzleActivator.Num(); i++){
		if(PuzzleActivator[i] != GameMode->ElemsPuzzle[i]){

			for(APuzzleButton* Butt : GameMode->ElemsPuzzle)
                Butt->Mesh->SetMaterial(0,RedColor);

		    GameMode->ElemsPuzzle.Empty();	
            GetWorld()->GetTimerManager().SetTimer(ResetPuzzleTimer,this,&ADoorOrderPuzzle::ResetPuzzle,0.5f,false);

			return;

		}
	}	

	for(APuzzleButton* Butt : PuzzleActivator){
        Butt->Mesh->SetMaterial(0,GreenColor);	
    	GameMode->ElemsPuzzle.Empty();
	}

	bOpenDoor = true;
    bSolved = true;

}

void ADoorOrderPuzzle::ResetPuzzle() {

	AGameModeTutorial* GameMode = Cast<AGameModeTutorial>(GetWorld()->GetAuthGameMode());

	for(APuzzleButton* Butt : PuzzleActivator){
        Butt->Mesh->SetMaterial(0,GreyColor);	
    	Butt->bDisableOverlap = false;
	}
	
    bSolved = true;
}
