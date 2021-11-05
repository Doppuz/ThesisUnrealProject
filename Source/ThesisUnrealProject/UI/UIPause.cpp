// Fill out your copyright notice in the Description page of Project Settings.


#include "UIPause.h"
#include "Components/TextBlock.h"
#include "Elements/UIButton.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Button.h"
#include "../GameModeAbstract.h"
#include "Kismet/GameplayStatics.h"
#include "../Character/CharacterPawnQuad.h"
#include "../Checkpoints/SaveGameOptions.h"

void UUIPause::NativeConstruct() {

    Super::NativeConstruct();

    ButtonResume->Text->SetText(FText::FromString("Resume"));
    ButtonResume->ButtonPlay->OnClicked.AddDynamic(this,&UUIPause::OnResumeClicked);

    ButtonRestart->Text->SetText(FText::FromString("Restart"));
    ButtonRestart->ButtonPlay->OnClicked.AddDynamic(this,&UUIPause::OnRestart);

    ButtonRestartAll->Text->SetText(FText::FromString("Beginning"));
    ButtonRestartAll->ButtonPlay->OnClicked.AddDynamic(this,&UUIPause::OnRestartAll);

    ButtonRestartLast->Text->SetText(FText::FromString("Last"));
    ButtonRestartLast->ButtonPlay->OnClicked.AddDynamic(this,&UUIPause::OnRestartLast);

    ButtonOptions->Text->SetText(FText::FromString("Options"));
    ButtonOptions->ButtonPlay->OnClicked.AddDynamic(this,&UUIPause::OnOptions);

    ButtonBack->Text->SetText(FText::FromString("Back"));
    ButtonBack->ButtonPlay->OnClicked.AddDynamic(this,&UUIPause::OnBack);
    
    ButtonBack2->Text->SetText(FText::FromString("Back"));
    ButtonBack2->ButtonPlay->OnClicked.AddDynamic(this,&UUIPause::OnBack);
        
    ButtonBack3->Text->SetText(FText::FromString("Back"));
    ButtonBack3->ButtonPlay->OnClicked.AddDynamic(this,&UUIPause::OnBack);

    ButtonCommands->Text->SetText(FText::FromString("Commands"));
    ButtonCommands->ButtonPlay->OnClicked.AddDynamic(this,&UUIPause::OnCommands);

    ButtonMenu->Text->SetText(FText::FromString("Menu"));
    ButtonMenu->ButtonPlay->OnClicked.AddDynamic(this,&UUIPause::OnMenu);

    CameraSlider->OnValueChanged.AddDynamic(this,&UUIPause::OnValueChanged);

    Switcher->SetActiveWidgetIndex(0);

}

void UUIPause::OnResumeClicked(){
 
	AGameModeAbstract* GameMode = Cast<AGameModeAbstract>(GetWorld()->GetAuthGameMode());
	GameMode->SetPause(false);

}

void UUIPause::OnRestartLast(){
 
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);

}

void UUIPause::OnRestart(){
 
	Switcher->SetActiveWidgetIndex(3);

}

void UUIPause::OnRestartAll(){
 
    FString CompleteFilePath = FPaths::ProjectSavedDir() + "SaveGames/CheckpointLevel1.sav"; 
    FPlatformFileManager::Get().GetPlatformFile().DeleteFile(*CompleteFilePath);

    CompleteFilePath = FPaths::ProjectSavedDir() + "SaveGames/Checkpoint.sav"; 
    FPlatformFileManager::Get().GetPlatformFile().DeleteFile(*CompleteFilePath);

	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);

}

void UUIPause::OnOptions(){
 
    ACharacterPawnQuad* Player = Cast<ACharacterPawnQuad>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
    CameraSlider->SetValue(Player->RotationSpeed);
	Switcher->SetActiveWidgetIndex(1);

}

void UUIPause::OnBack(){
 
	Switcher->SetActiveWidgetIndex(0);

    if (USaveGameOptions* SaveGameInstance = Cast<USaveGameOptions>(UGameplayStatics::CreateSaveGameObject(USaveGameOptions::StaticClass()))){

        ACharacterPawnQuad* Player = Cast<ACharacterPawnQuad>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
        SaveGameInstance->RotationSpeed = Player->RotationSpeed;

        // Start async save process.
		UGameplayStatics::AsyncSaveGameToSlot(SaveGameInstance, "Options", 0);

    }

}

void UUIPause::OnCommands(){
 
	Switcher->SetActiveWidgetIndex(2);

}

void UUIPause::OnValueChanged(float Value){
 
    ACharacterPawnQuad* Player = Cast<ACharacterPawnQuad>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
    Player->RotationSpeed = Value;

}

void UUIPause::OnMenu(){
 
	UGameplayStatics::OpenLevel(this, "MainMenu", false);

}