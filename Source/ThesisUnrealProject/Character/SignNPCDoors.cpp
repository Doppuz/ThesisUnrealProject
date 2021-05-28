// Fill out your copyright notice in the Description page of Project Settings.


#include "SignNPCDoors.h"
#include "CharacterPawnQuad.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "../GameModeTutorial.h"
#include "../Elements/Door.h"


ASignNPCDoors::ASignNPCDoors() {
}

//Choose which doors to open
void ASignNPCDoors::Choice(int Answer) {

	Super::Choice(Answer);
    
	AGameModeTutorial* GameMode = Cast<AGameModeTutorial>(GetWorld()->GetAuthGameMode());

	switch(Answer){
		case 0:
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

			break;
		case 1:
			SpeechContator += 2;

			//Open the right doors
            for(int Num : RightDoors)
            	GameMode->SetDoorOpen(Num);
			
			Speak();

			//Action taken by particular actors.
			switch (ID){
			case 0:
				GameMode->bLeft = false;
				break;
			
			default:
				break;
			}
			break;

		default:
			break;
	}
}
