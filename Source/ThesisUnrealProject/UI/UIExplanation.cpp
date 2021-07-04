// Fill out your copyright notice in the Description page of Project Settings.


#include "UIExplanation.h"
#include "Components/TextBlock.h"
#include "UIBox.h"
#include "UserWidgetList.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "UIButton.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UUIExplanation::NativeConstruct() {
    
    Super::NativeConstruct();

    Start->Text->SetText(FText::FromString("Start"));
    Start->ButtonPlay->OnClicked.AddDynamic(this,&UUIExplanation::OnSendClicked);

    TextBox->SetDialogText("Thanks for playing this test. Now I ask you to take a screenshot, click on the \"Send \" button and upload the file to the page that will open. If you have any problems contact me :).");

}

void UUIExplanation::OnSendClicked() {
    
    UGameplayStatics::GetPlayerController(GetWorld(),0)->SetInputMode(FInputModeGameOnly());
    UGameplayStatics::OpenLevel(GetWorld(),"Tutorial");

}

