// Fill out your copyright notice in the Description page of Project Settings.


#include "SignNPCGuessing.h"
#include "CharacterPawnQuad.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "../GameModeTutorial.h"
#include "../UI/UIWidgetDialog.h"
#include "../UI/UIBox.h"


ASignNPCGuessing::ASignNPCGuessing() {

}

//Choose which doors to open
void ASignNPCGuessing::Choice(int Answer) {
    
	if(Answer == 0){

	}else{
		
	}

}

void ASignNPCGuessing::Ask() {
	Super::Ask();

	AGameModeTutorial* GameMode = Cast<AGameModeTutorial>(GetWorld()->GetAuthGameMode());
	UUIWidgetDialog* DialogWidget = Cast<UUIWidgetDialog>(GameMode->GetCurrentWidgetUI());
	
	DialogWidget->AnswerBox->SetAnswer3(Questions[AnswerContator].Answers[2]);
	DialogWidget->AnswerBox->SetAnswer4(Questions[AnswerContator].Answers[3]);

	DialogWidget->AnswerBox->ViewListBoxGuessing();
}
