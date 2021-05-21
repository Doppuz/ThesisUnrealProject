// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnInteractiveClass.h"
#include "../GameModeTutorial.h"
#include "../UI/UIWidgetDialog.h"
#include "../Character/CharacterPawnQuad.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "AIController.h"
#include "../UI/UIWidgetDialog.h"
#include "../UI/UIBox.h"
#include "../Elements/Door.h"
#include "Components/BoxComponent.h"

// Sets default values
APawnInteractiveClass::APawnInteractiveClass()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	RootComponent = Collider;
	
	Collider->SetSimulatePhysics(true);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	bFocus = true;
}

// Called when the game starts or when spawned
void APawnInteractiveClass::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APawnInteractiveClass::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
	
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
	AGameModeTutorial* GameMode = Cast<AGameModeTutorial>(GetWorld()->GetAuthGameMode());
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
		
		if(QuestionAt < Speech.Num())
			QuestionAt = -1;

		switch(ID){
			case 0:
                Cast<ADoor>(GameMode->DoorActors[2])->bOpenDoor = true;
				UE_LOG(LogTemp, Warning, TEXT("AA %i"),GameMode->DoorActors.Num());
				break;
			case 2:
			case 3:
			case 4:
				GameMode->CheckPuzzle2(ID);
				break;
			default:
				break;
		}

		EndInteraction();
	}
}

//It asks the question.
void APawnInteractiveClass::Ask() {
	AGameModeTutorial* GameMode = Cast<AGameModeTutorial>(GetWorld()->GetAuthGameMode());
	UUIWidgetDialog* DialogWidget = Cast<UUIWidgetDialog>(GameMode->GetCurrentWidgetUI());
	
	ACharacterPawnQuad* PlayerPawn = Cast<ACharacterPawnQuad>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
	PlayerPawn->SetMousePointer(true);
	
	if(Questions.Num() > AnswerContator){
		
		DialogWidget->TextBox->SetDialogText(Questions[AnswerContator].Question);
		TArray<FString> TempAnswers = Questions[AnswerContator].Answers;

		DialogWidget->AnswerBox->SetAnswer1(Questions[AnswerContator].Answers[0]);
		DialogWidget->AnswerBox->SetAnswer2(Questions[AnswerContator].Answers[1]);

		DialogWidget->SetPopUpText("Choose the answer!");

		DialogWidget->ViewAnswerBox();

	}
}

void APawnInteractiveClass::StartInteraction() {
	AGameModeTutorial* GameMode = Cast<AGameModeTutorial>(GetWorld()->GetAuthGameMode());
	UUIWidgetDialog* DialogWidget = Cast<UUIWidgetDialog>(GameMode->GetCurrentWidgetUI());
	ACharacterPawnQuad* PlayerPawn = Cast<ACharacterPawnQuad>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
	PlayerPawn->AllyNPC = this;
	PlayerPawn->bStopMovement = true;

	//Cast<AAIController>(GetController())->GetBlackboardComponent()->SetValueAsBool(TEXT("NotEIsPressed"),false);
		
	APlayerController* PlayerController = Cast<APlayerController>(PlayerPawn->GetController());
	PlayerController->SetInputMode(FInputModeGameAndUI());

	if(DialogWidget != nullptr){
		DialogWidget->ViewSizeBox();
		Speak();
	}
}

void APawnInteractiveClass::EndInteraction() {
	AGameModeTutorial* GameMode = Cast<AGameModeTutorial>(GetWorld()->GetAuthGameMode());
	UUIWidgetDialog* DialogWidget = Cast<UUIWidgetDialog>(GameMode->GetCurrentWidgetUI());
	ACharacterPawnQuad* PlayerPawn = Cast<ACharacterPawnQuad>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
	PlayerPawn->SetMousePointer(false);
	PlayerPawn->AllyNPC = nullptr;
	PlayerPawn->bStopMovement = false;
	
	//Cast<AAIController>(GetController())->GetBlackboardComponent()->SetValueAsBool(TEXT("NotEIsPressed"),true);

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
	PlayerPawn->EquipmentMesh->SetStaticMesh(MeshToEquip);
}

void APawnInteractiveClass::Choice(int Answer) {
	
}



