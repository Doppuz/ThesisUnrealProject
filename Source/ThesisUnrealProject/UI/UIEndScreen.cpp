// Fill out your copyright notice in the Description page of Project Settings.


#include "UIEndScreen.h"
#include "Components/TextBlock.h"
#include "Elements/UIBox.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Elements/UIButton.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UUIEndScreen::NativeConstruct() {
    
    Super::NativeConstruct();

    Send->Text->SetText(FText::FromString("Send"));
    Send->ButtonPlay->OnClicked.AddDynamic(this,&UUIEndScreen::OnSendClicked);

    TextBox->SetDialogText("This is the end of the tutorial! You are now going to play a custom dungeon based on the choices you have made so far. Your aim is to reach the end of the maze. Now click on the play Button and enjoy!");

}

void UUIEndScreen::OnSendClicked() {
    
    //FPlatformProcess::LaunchURL(TEXT("https://forms.gle/Bxh3ifjAw7tBVCcz7"), NULL, NULL);
    
	//PlayerController->SetInputMode(FInputModeGameOnly());
    UGameplayStatics::OpenLevel(GetWorld(), Level, false);

}

void UUIEndScreen::OnQuitClicked() {
    if(UGameplayStatics::GetPlayerController(GetWorld(),0) != nullptr)
        UGameplayStatics::GetPlayerController(GetWorld(),0)->ConsoleCommand("exit");
    else
        UE_LOG(LogTemp,Warning,TEXT("Player is nullptr"));
}
