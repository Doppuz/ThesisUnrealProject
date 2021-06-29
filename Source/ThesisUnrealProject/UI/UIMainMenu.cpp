// Fill out your copyright notice in the Description page of Project Settings.


#include "UIMainMenu.h"
#include "Components/TextBlock.h"
#include "UIButton.h"
#include "UIAnswer.h"
#include "UIBox.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Border.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UUIMainMenu::NativeConstruct() {
    
    Super::NativeConstruct();

    ButtonPlay->Text->SetText(FText::FromString("Play"));
    ButtonPlay->ButtonPlay->OnClicked.AddDynamic(this,&UUIMainMenu::OnButtonPlayClicked);

    ButtonQuit->Text->SetText(FText::FromString("Quit"));
    ButtonQuit->ButtonPlay->OnClicked.AddDynamic(this,&UUIMainMenu::OnButtonQuitClicked);

    Switcher->SetActiveWidgetIndex(0);

    Answer1->SetVisibility(ESlateVisibility::Hidden);    
    Answer2->SetVisibility(ESlateVisibility::Hidden);

    TextBox->SetNPCName("");
    TextBox->BorderBox->SetBrushColor(FLinearColor(0.072917f,0.072917f,0.072917f,1.f));
    TextBox->SetDialogText("HI! Before Playing the game, I ask you to answer the question. Don't exit before finishing it.");

    TArray<FString> Temp;

    Temp.Init("Which is more enjoyable to you?","Killing a big monster","Bragging about it to your friends");
    MapDialogText[0] = Temp;

    /*Temp.Init("Which do you enjoy more in quests?","Getting involved in the storyline","Getting the rewards at the end");
    MapDialogText[1] = Temp;

    Temp.Init("Which is more enjoyable to you?","Killing a big monster","Bragging about it to your friends");
    MapDialogText[0] = Temp;
    Temp.Init("Which is more enjoyable to you?","Killing a big monster","Bragging about it to your friends");
    MapDialogText[0] = Temp;
    Temp.Init("Which is more enjoyable to you?","Killing a big monster","Bragging about it to your friends");
    MapDialogText[0] = Temp;
    Temp.Init("Which is more enjoyable to you?","Killing a big monster","Bragging about it to your friends");
    MapDialogText[0] = Temp;
    Temp.Init("Which is more enjoyable to you?","Killing a big monster","Bragging about it to your friends");
    MapDialogText[0] = Temp;
    Temp.Init("Which is more enjoyable to you?","Killing a big monster","Bragging about it to your friends");
    MapDialogText[0] = Temp;
    Temp.Init("Which is more enjoyable to you?","Killing a big monster","Bragging about it to your friends");
    MapDialogText[0] = Temp;
    Temp.Init("Which is more enjoyable to you?","Killing a big monster","Bragging about it to your friends");
    MapDialogText[0] = Temp;
    Temp.Init("Which is more enjoyable to you?","Killing a big monster","Bragging about it to your friends");
    MapDialogText[0] = Temp;
    Temp.Init("Which is more enjoyable to you?","Killing a big monster","Bragging about it to your friends");
    MapDialogText[0] = Temp;
    Temp.Init("Which is more enjoyable to you?","Killing a big monster","Bragging about it to your friends");
    MapDialogText[0] = Temp;
    Temp.Init("Which is more enjoyable to you?","Killing a big monster","Bragging about it to your friends");
    MapDialogText[0] = Temp;
    Temp.Init("Which is more enjoyable to you?","Killing a big monster","Bragging about it to your friends");
    MapDialogText[0] = Temp;
    Temp.Init("Which is more enjoyable to you?","Killing a big monster","Bragging about it to your friends");
    MapDialogText[0] = Temp;
    Temp.Init("Which is more enjoyable to you?","Killing a big monster","Bragging about it to your friends");
    MapDialogText[0] = Temp;
    Temp.Init("Which is more enjoyable to you?","Killing a big monster","Bragging about it to your friends");
    MapDialogText[0] = Temp;
    Temp.Init("Which is more enjoyable to you?","Killing a big monster","Bragging about it to your friends");
    MapDialogText[0] = Temp;
    Temp.Init("Which is more enjoyable to you?","Killing a big monster","Bragging about it to your friends");
    MapDialogText[0] = Temp;
    Temp.Init("Which is more enjoyable to you?","Killing a big monster","Bragging about it to your friends");
    MapDialogText[0] = Temp;
    Temp.Init("Which is more enjoyable to you?","Killing a big monster","Bragging about it to your friends");
    MapDialogText[0] = Temp;
    Temp.Init("Which is more enjoyable to you?","Killing a big monster","Bragging about it to your friends");
    MapDialogText[0] = Temp;
    Temp.Init("Which is more enjoyable to you?","Killing a big monster","Bragging about it to your friends");
    MapDialogText[0] = Temp;
    Temp.Init("Which is more enjoyable to you?","Killing a big monster","Bragging about it to your friends");
    MapDialogText[0] = Temp;
    Temp.Init("Which is more enjoyable to you?","Killing a big monster","Bragging about it to your friends");
    MapDialogText[0] = Temp;
    Temp.Init("Which is more enjoyable to you?","Killing a big monster","Bragging about it to your friends");
    MapDialogText[0] = Temp;
    Temp.Init("Which is more enjoyable to you?","Killing a big monster","Bragging about it to your friends");
    MapDialogText[0] = Temp;
    Temp.Init("Which is more enjoyable to you?","Killing a big monster","Bragging about it to your friends");
    MapDialogText[0] = Temp;*/

}

void UUIMainMenu::OnButtonPlayClicked() {
    
    //UGameplayStatics::OpenLevel(GetWorld(), "Tutorial");
    Switcher->SetActiveWidgetIndex(1);

}

void UUIMainMenu::OnButtonQuitClicked() {

    UGameplayStatics::GetPlayerController(GetWorld(),0)->ConsoleCommand("quit");
    
}