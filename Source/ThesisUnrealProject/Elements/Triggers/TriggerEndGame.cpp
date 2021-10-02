// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerEndGame.h"
#include "Components/BoxComponent.h"
#include "../../Character/CharacterPawnQuad.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/LevelStreaming.h"
#include "Components/SpotLightComponent.h"
#include "../../GameModeTutorial.h"
#include "../../UI/UIEndScreen.h"

// Sets default values
ATriggerEndGame::ATriggerEndGame(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void ATriggerEndGame::OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit) {
	
	if(OtherActor->IsA(ACharacterPawnQuad::StaticClass())){
		ACharacterPawnQuad* MyPawn = Cast<ACharacterPawnQuad>(OtherActor);
		
		if(MyPawn->GetController()->IsA(APlayerController::StaticClass())){

			AGameModeTutorial* GameMode = Cast<AGameModeTutorial>(GetWorld()->GetAuthGameMode());

    		UGameplayStatics::GetPlayerController(GetWorld(),0)->SetInputMode(FInputModeUIOnly());
			UGameplayStatics::GetPlayerController(GetWorld(),0)->SetShowMouseCursor(true);
			Cast<APlayerController>(MyPawn->GetController())->SetPause(true);

			GameMode->ChangeMenuWidget(UIEndGame);

			UUIEndScreen* EndScreen = Cast<UUIEndScreen>(GameMode->GetCurrentWidgetUI());
			
			GameMode->Update->SaveFile("");

			EndScreen->SetTestValue(GameMode->Update->Types[Type::Achiever],GameMode->Update->Types[Type::Explorer],GameMode->Update->Types[Type::Killer],GameMode->Update->Types[Type::Socializer]);
			EndScreen->SetQuestionaryValue(GameMode->Update->TypesQuestionary[Type::Achiever],GameMode->Update->TypesQuestionary[Type::Explorer],GameMode->Update->TypesQuestionary[Type::Killer],GameMode->Update->TypesQuestionary[Type::Socializer]);
			
			FString file = FPaths::ProjectSavedDir();
    		file.Append(TEXT("SaveGames/Checkpoint.sav"));

    		// We will use this FileManager to deal with the file.
    		IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile();

			bool Result = FileManager.DeleteFile(*file);

			if(Result){
				UE_LOG(LogTemp,Warning,TEXT("true %s"),*file);
			}else {
				UE_LOG(LogTemp,Warning,TEXT("%s"),*file);
			}

		}
	}

}
