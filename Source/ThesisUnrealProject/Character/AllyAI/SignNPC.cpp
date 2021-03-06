// Fill out your copyright notice in the Description page of Project Settings.


#include "SignNPC.h"
#include "../CharacterPawnQuad.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "../../GameModeTutorial.h"

ASignNPC::ASignNPC() {

}

//Choose which doors to open
void ASignNPC::Choice(int Answer) {
    
	AGameModeTutorial* GameMode = Cast<AGameModeTutorial>(GetWorld()->GetAuthGameMode());
    ACharacterPawnQuad* PlayerPawn = Cast<ACharacterPawnQuad>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
	PlayerPawn->SetMousePointer(false);
	APlayerController* PlayerController = Cast<APlayerController>(PlayerPawn->GetController());
	PlayerController->SetInputMode(FInputModeGameOnly());

}
