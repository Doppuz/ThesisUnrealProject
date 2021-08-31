// Fill out your copyright notice in the Description page of Project Settings.


#include "RiddleNPC.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "../../GameModeAbstract.h"
#include "../../UI/UIWidgetDialog.h"
#include "../../UI/Elements/UIBox.h"


ARiddleNPC::ARiddleNPC() {
	RightAnswerPos = 0;
}

//Choose which doors to open
void ARiddleNPC::Choice(int Answer) {
    
	if(RightAnswerPos == Answer){
		SpeechContator += 1;
		
		Speak();

		LeftChoice.Broadcast();
		Solved.Broadcast(this);
		
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
		AGameModeAbstract* GameMode = Cast<AGameModeAbstract>(GetWorld()->GetAuthGameMode());
		UUIWidgetDialog* DialogWidget = Cast<UUIWidgetDialog>(GameMode->GetCurrentWidgetUI());
	
		DialogWidget->AnswerBox->SetAnswer1(Questions[AnswerContator].Answers[2]);
		DialogWidget->AnswerBox->SetAnswer4(Questions[AnswerContator].Answers[3]);

		DialogWidget->AnswerBox->ViewListBoxGuessing();
	
	}
}
