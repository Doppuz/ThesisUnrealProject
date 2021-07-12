// Fill out your copyright notice in the Description page of Project Settings.


#include "UIEndScreen.h"
#include "Components/TextBlock.h"
#include "UIBox.h"
#include "UserWidgetList.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "UIButton.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UUIEndScreen::NativeConstruct() {
    
    Super::NativeConstruct();

    Send->Text->SetText(FText::FromString("Send"));
    Send->ButtonPlay->OnClicked.AddDynamic(this,&UUIEndScreen::OnSendClicked);

    Quit->Text->SetText(FText::FromString("Quit"));
    Quit->ButtonPlay->OnClicked.AddDynamic(this,&UUIEndScreen::OnQuitClicked);

    TextBox->SetDialogText("Thanks for playing this test. Now I ask you to take a screenshot, click on the \"Send \" button and upload the file to the page that will open. If you have any problems contact me :).");

}

void UUIEndScreen::SetTestValue(float AchieverValue, float ExplorerValue, float KillerValue, float SocializerValue) {

    Achiever->SetText(FText::Format(NSLOCTEXT("CoinsKey","CoinsSource", "Achiever : {0}"), AchieverValue));
    Explorer->SetText(FText::Format(NSLOCTEXT("CoinsKey","CoinsSource", "Explorer : {0}"), ExplorerValue));
    Killer->SetText(FText::Format(NSLOCTEXT("CoinsKey","CoinsSource", "Killer : {0}"), KillerValue));
    Socializer->SetText(FText::Format(NSLOCTEXT("CoinsKey","CoinsSource", "Socializer : {0}"), SocializerValue));

}

void UUIEndScreen::SetQuestionaryValue(float AchieverValue, float ExplorerValue, float KillerValue, float SocializerValue) {
    
    AchieverQ->SetText(FText::Format(NSLOCTEXT("CoinsKey","CoinsSource", "Achiever : {0}"), AchieverValue));
    ExplorerQ->SetText(FText::Format(NSLOCTEXT("CoinsKey","CoinsSource", "Explorer : {0}"), ExplorerValue));
    KillerQ->SetText(FText::Format(NSLOCTEXT("CoinsKey","CoinsSource", "Killer : {0}"), KillerValue));
    SocializerQ->SetText(FText::Format(NSLOCTEXT("CoinsKey","CoinsSource", "Socializer : {0}"), SocializerValue));

}

void UUIEndScreen::OnSendClicked() {
    FPlatformProcess::LaunchURL(TEXT("https://forms.gle/Bxh3ifjAw7tBVCcz7"), NULL, NULL);
}

void UUIEndScreen::OnQuitClicked() {
    if(UGameplayStatics::GetPlayerController(GetWorld(),0) != nullptr)
        UGameplayStatics::GetPlayerController(GetWorld(),0)->ConsoleCommand("exit");
    else
        UE_LOG(LogTemp,Warning,TEXT("Player is nullptr"));
}
