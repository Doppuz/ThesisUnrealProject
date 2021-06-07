// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCRumbleSpawn.h"
#include "CharacterPawnQuad.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "../GameModeTutorial.h"
#include "../Elements/Door.h"
#include "../Elements/RumbleArena.h"


ANPCRumbleSpawn::ANPCRumbleSpawn() {

}

//Choose which doors to open
void ANPCRumbleSpawn::Choice(int Answer) {
    
	AGameModeTutorial* GameMode = Cast<AGameModeTutorial>(GetWorld()->GetAuthGameMode());
	ACharacterPawnQuad* PlayerPawn = Cast<ACharacterPawnQuad>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
	PlayerPawn->SetMousePointer(false);
	APlayerController* PlayerController = Cast<APlayerController>(PlayerPawn->GetController());
	PlayerController->SetInputMode(FInputModeGameOnly());

	switch(Answer){
		case 0:

			if(Arena != nullptr){
				Arena->RewardClass = RewardClass;
			}

			for(int Num : LeftDoors)
            	GameMode->SetDoorOpen(Num);

			SpeechContator += 1;
			Speak();
			SpeechContator += 1;
			
			QuestionAt = -1;

			break;
		case 1:

			for(int Num : RightDoors)
            	GameMode->SetDoorOpen(Num);

			PlayerPawn->ProjectileTimeout = 0.3f;
			SpeechContator += 2;
			Speak();
			
			QuestionAt = -1;

			break;
		default:
			break;
	}
}
