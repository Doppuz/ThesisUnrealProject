// Fill out your copyright notice in the Description page of Project Settings.


#include "UIExplanation.h"
#include "Components/TextBlock.h"
#include "Elements/UIBox.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Elements/UIButton.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Border.h"
#include "../Levels/MainMenu.h"

void UUIExplanation::NativeConstruct() {
    
    Super::NativeConstruct();

    Start->Text->SetText(FText::FromString("Start"));
    Start->ButtonPlay->OnClicked.AddDynamic(this,&UUIExplanation::OnSendClicked);

    TextBox->SetDialogText("Let's now jump into the test. First thing you need to know is that you can choose how to play the levels. There will be always two different choices and you can choose what you prefer. Are you ready?");
    TextBox->BorderBox->SetBrushColor(FLinearColor(0.072917f,0.072917f,0.072917f,0.8f));
    TextBox->SetNPCName("");
}

void UUIExplanation::OnSendClicked() {

    ULevel* LevelTemp = GetWorld()->GetCurrentLevel();
    Cast<AMainMenu>(LevelTemp->GetLevelScriptActor())->ChangeMenuWidget(nullptr);
    
    UGameplayStatics::OpenLevel(GetWorld(),"Tutorial",false);

}

