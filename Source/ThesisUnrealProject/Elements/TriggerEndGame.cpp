// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerEndGame.h"
#include "Components/BoxComponent.h"
#include "../Projectile/SquaredProjectile.h"
#include "../Character/AICharacterPawnQuad.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/LevelStreaming.h"
#include "Components/SpotLightComponent.h"
#include "../GameModeTutorial.h"
#include "../UI/UIEndScreen.h"
#include "../GameInstance/BartleManagerGameInstance.h"

// Sets default values
ATriggerEndGame::ATriggerEndGame(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


// Called when the game starts or when spawned
void ATriggerEndGame::BeginPlay(){
	
	Super::BeginPlay();

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
			
			UBartleManagerGameInstance* Bartle = Cast<UBartleManagerGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
			Bartle->SaveFile("");

			EndScreen->SetTestValue(Bartle->Types[Type::Achiever],Bartle->Types[Type::Explorer],Bartle->Types[Type::Killer],Bartle->Types[Type::Socializer]);
			EndScreen->SetQuestionaryValue(Bartle->TypesQuestionary[Type::Achiever],Bartle->TypesQuestionary[Type::Explorer],Bartle->TypesQuestionary[Type::Killer],Bartle->TypesQuestionary[Type::Socializer]);

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

// Called every frame
void ATriggerEndGame::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

}