// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCEquipment.h"
#include "CharacterPawnQuad.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "../GameModeTutorial.h"
#include "../Elements/Door.h"


ANPCEquipment::ANPCEquipment() {

}

//Choose which doors to open
void ANPCEquipment::Choice(int Answer) {

	Super::Choice(Answer);
    
	ACharacterPawnQuad* PlayerPawn = Cast<ACharacterPawnQuad>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
	PlayerPawn->SetMousePointer(false);
	APlayerController* PlayerController = Cast<APlayerController>(PlayerPawn->GetController());
	PlayerController->SetInputMode(FInputModeGameOnly());

	switch(Answer){
		case 0:
			Equipment();
			SpeechContator += 1;
			Speak();
			SpeechContator += 1;
			break;
		case 1:
			SpeechContator += 2;
			Speak();
			break;
		default:
			break;
	}
}
