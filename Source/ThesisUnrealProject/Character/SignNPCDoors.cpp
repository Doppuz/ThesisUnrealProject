// Fill out your copyright notice in the Description page of Project Settings.


#include "SignNPCDoors.h"
#include "CharacterPawnQuad.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "../GameModeTutorial.h"
#include "../Elements/Door.h"
#include "../UI/UIWidgetDialog.h"
#include "../UI/UIBox.h"


ASignNPCDoors::ASignNPCDoors() {
	RightAnswerPos = 0;
}

//Choose which doors to open
void ASignNPCDoors::Choice(int Answer) {
    
	if(RightAnswerPos == Answer){
		
		LeftChoice.Broadcast();

	}else{
		
		RightChoice.Broadcast();

	}
}

void ASignNPCDoors::Ask() {
	Super::Ask();

	if(Questions[AnswerContator].Answers.Num() > 2){
		AGameModeTutorial* GameMode = Cast<AGameModeTutorial>(GetWorld()->GetAuthGameMode());
		UUIWidgetDialog* DialogWidget = Cast<UUIWidgetDialog>(GameMode->GetCurrentWidgetUI());
	
		DialogWidget->AnswerBox->SetAnswer3(Questions[AnswerContator].Answers[2]);
		DialogWidget->AnswerBox->SetAnswer4(Questions[AnswerContator].Answers[3]);

		DialogWidget->AnswerBox->ViewListBoxGuessing();
	
	}
}
