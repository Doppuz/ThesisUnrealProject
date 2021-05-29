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

	Super::Choice(Answer);
    
	AGameModeTutorial* GameMode = Cast<AGameModeTutorial>(GetWorld()->GetAuthGameMode());

	if(RightAnswerPos == Answer){
		
		SpeechContator += 1;

		//Open the left doors
		for(int Num : LeftDoors)
            GameMode->SetDoorOpen(Num);
			
		Speak();
		SpeechContator += 1;

		//Action taken by particular actors.
		switch (ID){
		case 0:
			GameMode->bLeft = true;
			break;
			
		default:
			break;
		}

		QuestionAt = -1;

	}else{
		
		SpeechContator += 2;

		//Open the right doors
        for(int Num : RightDoors)
            GameMode->SetDoorOpen(Num);
			
		Speak();

		//Action taken by particular actors.
		switch (ID){
		case 0:
			GameMode->bLeft = false;
			QuestionAt = -1;
			break;
			
		default:
			break;
		}

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
