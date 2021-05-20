// Fill out your copyright notice in the Description page of Project Settings.


#include "SignNPC.h"
#include "CharacterPawnQuad.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "../GameModeTutorial.h"
#include "../Elements/Door.h"


ASignNPC::ASignNPC() {
    Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	RootComponent = Collider;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
}

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
            Cast<ADoor>(GameMode->DoorActors[3])->bOpenDoor = true;
            Cast<ADoor>(GameMode->DoorActors[4])->bOpenDoor = true;
			Speak();
			SpeechContator += 1;
			break;
		case 1:
			SpeechContator += 2;
			GameMode->bLeft = false;
            Cast<ADoor>(GameMode->DoorActors[5])->bOpenDoor = true;
            Cast<ADoor>(GameMode->DoorActors[6])->bOpenDoor = true;
			Speak();
			break;
		default:
			break;
	}
}
