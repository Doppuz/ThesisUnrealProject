// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnInteractiveClass.h"
#include "../../GameModeTutorial.h"
#include "../CharacterPawnQuad.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "AIController.h"
#include "../../UI/UIWidgetDialog.h"
#include "../../UI/Elements/UIBox.h"
#include "../../Elements/GeneralElements/Doors/Door.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../../Elements/Statue/StatueInteractElem.h"

int APawnInteractiveClass::IDCount = 0;

// Sets default values
APawnInteractiveClass::APawnInteractiveClass()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	RootComponent = Collider;
	
	Collider->SetCollisionProfileName("InteractiveElement");

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	Mesh->SetCollisionProfileName("NoCollision");

	bFocus = true;
	bAlreadySpoken = false;
	bNoIncrease = false;
	QuestionAt = 200;
}

void APawnInteractiveClass::BeginPlay(){

	Super::BeginPlay();

	ID = IDCount;
	IDCount = (IDCount + 1) % 50000;

	UGameplayStatics::GetPlayerPawn(GetWorld(),0)->MoveIgnoreActorAdd(this);

	if(!bNoIncrease){
		
		AGameModeAbstract* GameMode = Cast<AGameModeAbstract>(GetWorld()->GetAuthGameMode());

		GameMode->TotalAllies += 1;
			
	}

}

// Called every frame
void APawnInteractiveClass::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
	
	//Set the focus from the AI to the player.
	if(bFocus){
		APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
	
		FVector NewPos = (GetActorLocation() - PlayerPawn->GetActorLocation());
		NewPos.Z = 0;
		NewPos.Normalize();
	
		SetActorRotation(FMath::RInterpTo(GetActorRotation(),NewPos.Rotation(),DeltaTime * 100,0.4));
	}

}

// Called to bind functionality to input
void APawnInteractiveClass::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent){
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

/*Change the text in the dialog box. If I have already answer the question, It shows only the last answer.*/
void APawnInteractiveClass::Speak() {
	AGameModeAbstract* GameMode = Cast<AGameModeAbstract>(GetWorld()->GetAuthGameMode());
	UUIWidgetDialog* DialogWidget = Cast<UUIWidgetDialog>(GameMode->GetCurrentWidgetUI());
	
	DialogWidget->SetPopUpText("Press E to continue...");
	
	if(Speech.Num() > SpeechContator){
		if(QuestionAt != -1)
			DialogWidget->TextBox->SetDialogText(Speech[SpeechContator]);
		else{
			DialogWidget->TextBox->SetDialogText(Speech[Speech.Num() - 1]);
			SpeechContator = Speech.Num() - 1;
		}
	}else{
		SpeechContator = 0;
		AnswerContator = 0;

		if(QuestionAt != -1 && QuestionAt < Speech.Num())
			QuestionAt = -1;

		EndDialog.Broadcast(this);

		if(!bAlreadySpoken && !bNoIncrease){

			GameMode->IncreaseAllies();
			UE_LOG(LogTemp,Warning,TEXT("Allies: %i"), GameMode->GetAllies());
			
		}

		bAlreadySpoken = true;

		EndInteraction();
	}
}

//It asks the question.
void APawnInteractiveClass::Ask() {
	AGameModeAbstract* GameMode = Cast<AGameModeAbstract>(GetWorld()->GetAuthGameMode());
	UUIWidgetDialog* DialogWidget = Cast<UUIWidgetDialog>(GameMode->GetCurrentWidgetUI());
	
	ACharacterPawnQuad* PlayerPawn = Cast<ACharacterPawnQuad>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
	PlayerPawn->SetMousePointer(true);
	
	if(Questions.Num() > AnswerContator){
		
		DialogWidget->TextBox->SetDialogText(Questions[AnswerContator].Question);
		TArray<FString> TempAnswers = Questions[AnswerContator].Answers;

		DialogWidget->AnswerBox->SetAnswer2(Questions[AnswerContator].Answers[0]);
		DialogWidget->AnswerBox->SetAnswer3(Questions[AnswerContator].Answers[1]);

		DialogWidget->SetPopUpText("Choose the answer!");

		DialogWidget->ViewAnswerBox();

	}
}

void APawnInteractiveClass::StartInteraction() {
	AGameModeAbstract* GameMode = Cast<AGameModeAbstract>(GetWorld()->GetAuthGameMode());
	UUIWidgetDialog* DialogWidget = Cast<UUIWidgetDialog>(GameMode->GetCurrentWidgetUI());
	ACharacterPawnQuad* PlayerPawn = Cast<ACharacterPawnQuad>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
	PlayerPawn->AllyNPC = this;
	PlayerPawn->bStopMovement = true;
	PlayerPawn->bCharacterInvincible = true;
		
	APlayerController* PlayerController = Cast<APlayerController>(PlayerPawn->GetController());
	PlayerController->SetInputMode(FInputModeGameAndUI());

	if(DialogWidget != nullptr){
		DialogWidget->ViewSizeBox();
		Speak();
	}
}

void APawnInteractiveClass::EndInteraction() {
	AGameModeAbstract* GameMode = Cast<AGameModeAbstract>(GetWorld()->GetAuthGameMode());
	UUIWidgetDialog* DialogWidget = Cast<UUIWidgetDialog>(GameMode->GetCurrentWidgetUI());
	ACharacterPawnQuad* PlayerPawn = Cast<ACharacterPawnQuad>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
	PlayerPawn->SetMousePointer(false);
	PlayerPawn->AllyNPC = nullptr;
	PlayerPawn->bStopMovement = false;
	PlayerPawn->bCharacterInvincible = false;

	APlayerController* PlayerController = Cast<APlayerController>(PlayerPawn->GetController());
	PlayerController->SetInputMode(FInputModeGameOnly());

	if(DialogWidget != nullptr){
		DialogWidget->HideSizeBox();
		DialogWidget->HideAnswerBox();
		DialogWidget->SetPopUpText("Press E to interact.");
	}
}

//It equips the object.
void APawnInteractiveClass::Equipment() {
	
	ACharacterPawnQuad* PlayerPawn = Cast<ACharacterPawnQuad>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));

}

void APawnInteractiveClass::Choice(int Answer) {
	ACharacterPawnQuad* PlayerPawn = Cast<ACharacterPawnQuad>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
	PlayerPawn->SetMousePointer(false);
	APlayerController* PlayerController = Cast<APlayerController>(PlayerPawn->GetController());
	PlayerController->SetInputMode(FInputModeGameOnly());

	switch(Answer){
		case 0:	
			LeftChoice.Broadcast();
			SpeechContator += 1;
			Speak();
			SpeechContator = Speech.Num() - 1;
			Speak();
			break;
		case 1:
			RightChoice.Broadcast();
			SpeechContator += 1;
			Speak();
			break;
		default:
			break;
	}
}
