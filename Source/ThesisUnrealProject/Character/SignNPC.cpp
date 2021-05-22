// Fill out your copyright notice in the Description page of Project Settings.


#include "SignNPC.h"
#include "CharacterPawnQuad.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "../GameModeTutorial.h"
#include "../Elements/Door.h"


ASignNPC::ASignNPC() {

}

//Choose which doors to open
void ASignNPC::Choice(int Answer) {
    
	AGameModeTutorial* GameMode = Cast<AGameModeTutorial>(GetWorld()->GetAuthGameMode());
    ACharacterPawnQuad* PlayerPawn = Cast<ACharacterPawnQuad>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
	PlayerPawn->SetMousePointer(false);
	APlayerController* PlayerController = Cast<APlayerController>(PlayerPawn->GetController());
	PlayerController->SetInputMode(FInputModeGameOnly());

	switch(Answer){
		case 0:
			SpeechContator += 1;
			GameMode->bLeft = true;
            GameMode->SetDoorOpen(3);
			GameMode->SetDoorOpen(4);
			Speak();
			SpeechContator += 1;
			break;
		case 1:
			SpeechContator += 2;
			GameMode->bLeft = false;
            GameMode->SetDoorOpen(5);
			GameMode->SetDoorOpen(6);
			Speak();
			break;
		default:
			break;
	}
}
