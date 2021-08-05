// Fill out your copyright notice in the Description page of Project Settings.


#include "RiddleNPC.h"
#include "CharacterPawnQuad.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "../GameModeTutorial.h"
#include "../Elements/Door.h"
#include "../UI/UIWidgetDialog.h"
#include "../UI/UIBox.h"


ARiddleNPC::ARiddleNPC() {
	RightAnswerPos = 0;
}

//Choose which doors to open
void ARiddleNPC::Choice(int Answer) {
    
	if(RightAnswerPos == Answer){
		SpeechContator += 1;
		
		Speak();

		LeftChoice.Broadcast();
		
		SpeechContator = Speech.Num() - 2;

	}else{
		
		SpeechContator += 2;
		
		Speak();

		RightChoice.Broadcast();


	}
}

void ARiddleNPC::Ask() {
	Super::Ask();

	if(Questions[AnswerContator].Answers.Num() > 2){
		AGameModeTutorial* GameMode = Cast<AGameModeTutorial>(GetWorld()->GetAuthGameMode());
		UUIWidgetDialog* DialogWidget = Cast<UUIWidgetDialog>(GameMode->GetCurrentWidgetUI());
	
		DialogWidget->AnswerBox->SetAnswer1(Questions[AnswerContator].Answers[2]);
		DialogWidget->AnswerBox->SetAnswer4(Questions[AnswerContator].Answers[3]);

		DialogWidget->AnswerBox->ViewListBoxGuessing();
	
	}
}
