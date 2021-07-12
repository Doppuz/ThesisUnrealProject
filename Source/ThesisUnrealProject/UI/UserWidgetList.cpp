// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgetList.h"
#include "Components/ListView.h"
#include "UIAnswer.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "../Character/CharacterPawnQuad.h"
#include "../Character/PawnInteractiveClass.h"

void UUserWidgetList::NativeConstruct() {
    HideListBox();
    
    Answer1->AnswerButton->OnClicked.AddDynamic(this,&UUserWidgetList::OnButton1Clicked);
    Answer2->AnswerButton->OnClicked.AddDynamic(this,&UUserWidgetList::OnButton2Clicked);
    Answer3->AnswerButton->OnClicked.AddDynamic(this,&UUserWidgetList::OnButton3Clicked);
    Answer4->AnswerButton->OnClicked.AddDynamic(this,&UUserWidgetList::OnButton4Clicked);
}

/*void UUserWidgetList::AddElement() {
    UUIAnswer* CurrentWidget = CreateWidget<UUIAnswer>(GetWorld(), AnswerWidgetClass);
    CurrentWidget->Answer->SetText(FText::FromString("32"));
    AnswerList.Add(CurrentWidget);
    List->AddItem(CurrentWidget);
}

void UUserWidgetList::SetText(TArray<FString> TextList) {
    for(int i = 0; i < TextList.Num(); i++){
        Cast<UUIAnswer>(List->GetItemAt(0))->SetAnswerText("TextList[i]");
    }
    UE_LOG(LogTemp,Warning, TEXT("%s"), *Cast<UUIAnswer>(List->GetItemAt(0))->Answer->GetText().ToString());
}

void UUserWidgetList::ResetList() {
    List->ClearListItems();
}*/

void UUserWidgetList::SetAnswer1(FString Response) {
    Answer1->SetAnswerText(Response);
}

void UUserWidgetList::SetAnswer2(FString Response) {
    Answer2->SetAnswerText(Response);
}

void UUserWidgetList::SetAnswer3(FString Response) {
    Answer3->SetAnswerText(Response);
}

void UUserWidgetList::SetAnswer4(FString Response) {
    Answer4->SetAnswerText(Response);
}

void UUserWidgetList::OnButton1Clicked() {

    ACharacterPawnQuad* PlayerPawn = Cast<ACharacterPawnQuad>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
    HideListBox();
    PlayerPawn->AllyNPC->Choice(2);

}

void UUserWidgetList::OnButton3Clicked() {
    
    ACharacterPawnQuad* PlayerPawn = Cast<ACharacterPawnQuad>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
    HideListBox();
    PlayerPawn->AllyNPC->Choice(1);
    
}

void UUserWidgetList::OnButton4Clicked() {

    ACharacterPawnQuad* PlayerPawn = Cast<ACharacterPawnQuad>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
    HideListBox();
    PlayerPawn->AllyNPC->Choice(3);

}

void UUserWidgetList::OnButton2Clicked() {
    
    ACharacterPawnQuad* PlayerPawn = Cast<ACharacterPawnQuad>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
    HideListBox();
    PlayerPawn->AllyNPC->Choice(0);
    
}

void UUserWidgetList::ViewListBox() {
    Answer2->SetVisibility(ESlateVisibility::Visible);
    Answer3->SetVisibility(ESlateVisibility::Visible);
}

void UUserWidgetList::HideListBox() {
    Answer1->SetVisibility(ESlateVisibility::Hidden);
    Answer2->SetVisibility(ESlateVisibility::Hidden);
    Answer3->SetVisibility(ESlateVisibility::Hidden);
    Answer4->SetVisibility(ESlateVisibility::Hidden);
}

void UUserWidgetList::ViewListBoxGuessing() {
    Answer1->SetVisibility(ESlateVisibility::Visible);
    Answer2->SetVisibility(ESlateVisibility::Visible);
    Answer3->SetVisibility(ESlateVisibility::Visible);
    Answer4->SetVisibility(ESlateVisibility::Visible);
}