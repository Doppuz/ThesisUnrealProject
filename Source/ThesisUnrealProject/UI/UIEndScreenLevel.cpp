// Fill out your copyright notice in the Description page of Project Settings.


#include "UIEndScreenLevel.h"
#include "Components/TextBlock.h"
#include "Elements/UIBox.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Elements/UIButton.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UUIEndScreenLevel::NativeConstruct() {
    
    Super::NativeConstruct();

    Send->Text->SetText(FText::FromName("Send"));
    Send->ButtonPlay->OnClicked.AddDynamic(this,&UUIEndScreenLevel::OnSendClicked);

    Play->Text->SetText(FText::FromName("Menu"));
    Play->ButtonPlay->OnClicked.AddDynamic(this,&UUIEndScreenLevel::OnQuitClicked);

    TextBox->SetDialogText(Text.ToString());

}

void UUIEndScreenLevel::OnSendClicked() {
    
    //FPlatformProcess::LaunchURL(TEXT("https://forms.gle/Bxh3ifjAw7tBVCcz7"), NULL, NULL);
    
	//PlayerController->SetInputMode(FInputModeGameOnly());
    UGameplayStatics::OpenLevel(GetWorld(), Level, false);

}

void UUIEndScreenLevel::OnQuitClicked() {

    UGameplayStatics::OpenLevel(GetWorld(), "MainMenu", false);

}
