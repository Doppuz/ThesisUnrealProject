// Fill out your copyright notice in the Description page of Project Settings.


#include "SignNPCDoorsActiveTrigger.h"
#include "CharacterPawnQuad.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "../GameModeTutorial.h"
#include "../Elements/Door.h"
#include "../UI/UIWidgetDialog.h"
#include "../UI/UIBox.h"
#include "../Elements/Trigger.h"


ASignNPCDoorsActiveTrigger::ASignNPCDoorsActiveTrigger() {
	RightAnswerPos = 0;
}

//Choose which doors to open
void ASignNPCDoorsActiveTrigger::Choice(int Answer) {

	Super::Choice(Answer);
    
	AGameModeTutorial* GameMode = Cast<AGameModeTutorial>(GetWorld()->GetAuthGameMode());

	if(RightAnswerPos == Answer){
		
		SpeechContator += 1;

		//Open the left doors
		for(int Num : LeftDoors)
            GameMode->SetDoorOpen(Num);
			
		Speak();
		SpeechContator += 1;

		QuestionAt = -1;

	}else{
		
		SpeechContator += 2;

		TriggerActor->Trigger->SetCollisionProfileName("NoCollision");

		//Open the right doors
        for(int Num : RightDoors)
            GameMode->SetDoorOpen(Num);
			
		Speak();


	}
}

