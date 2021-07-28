// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeTutorial.h"
#include "Elements/PuzzleButton.h"
#include "Elements/Door.h"
#include "Kismet/GameplayStatics.h"
#include "UI/UIWidgetDialog.h"
#include "UI/UIBox.h"
#include "CustomGameState.h"
#include "Engine/TriggerVolume.h"
#include "CheckPoints/SaveGameData.h"
#include "CustomGameState.h"
#include "Engine/LevelStreaming.h"

AGameModeTutorial::AGameModeTutorial() {
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AGameModeTutorial::BeginPlay() {

    // Retrieve and cast the USaveGame object to UMySaveGame.
    if (USaveGameData* LoadedGame = Cast<USaveGameData>(UGameplayStatics::LoadGameFromSlot("Checkpoint", 0))){
        
        // The operation was successful, so LoadedGame now contains the data we saved earlier.
        // Load the position only if I don't come from the main menu.
        if(LoadedGame->PlayerLocation != FVector(0.f,0.f,900000.22f))
            UGameplayStatics::GetPlayerPawn(GetWorld(),0)->SetActorLocation(LoadedGame->PlayerLocation);

        /*UBartleManagerGameInstance* Bartle = Cast<UBartleManagerGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

        //Load the bartle's type data.
        Bartle->Types[Type::Achiever] = LoadedGame->Achiever;
        Bartle->Types[Type::Explorer] = LoadedGame->Explorer;
        Bartle->Types[Type::Killer] = LoadedGame->Killer;
        Bartle->Types[Type::Socializer] = LoadedGame->Socializer;

        Bartle->TypesQuestionary[Type::Achiever] = LoadedGame->AchieverQ;
        Bartle->TypesQuestionary[Type::Explorer] = LoadedGame->ExplorerQ;
        Bartle->TypesQuestionary[Type::Killer] = LoadedGame->KillerQ;
        Bartle->TypesQuestionary[Type::Socializer] = LoadedGame->SocializerQ;*/

        //Load levels
        Levels = LoadedGame->Levels;
  
        if(Levels.Num() != 0){
            FLatentActionInfo LatentInfo;	
            UGameplayStatics::LoadStreamLevel(this, Levels[0], true, false, LatentInfo);
            
            if(Levels.Num() > LevelContator){
                ULevelStreaming* Level = UGameplayStatics::GetStreamingLevel(GetWorld(), Levels[0]);
                Level->OnLevelLoaded.AddDynamic(this,&AGameModeTutorial::OnLevelLoad);
            }
        }

    }else{
        
        FLatentActionInfo LatentInfo;	
        UGameplayStatics::LoadStreamLevel(this, "FirstPuzzle", true, false, LatentInfo);

        Levels.Add("FirstPuzzle");

    }

    ChangeMenuWidget(WidgetClass);

	UUIWidgetDialog* DialogWidget = Cast<UUIWidgetDialog>(CurrentWidget);
    DialogWidget->HideSizeBox();
    DialogWidget->TextBox->BoxContainer->Visibility = ESlateVisibility::Hidden;
}

//Assign the UI widget passed as parameter to the screen.
void AGameModeTutorial::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass) {
    if (CurrentWidget != nullptr){
        CurrentWidget->RemoveFromViewport();
        CurrentWidget = nullptr;
    }
    if (NewWidgetClass != nullptr){
        CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
        if (CurrentWidget != nullptr){
            CurrentWidget->AddToViewport();
        }
    }
}

//Get current UI
UUserWidget* AGameModeTutorial::GetCurrentWidgetUI() {
    return CurrentWidget;
}

//--- Get and Set for the coins

int AGameModeTutorial::GetCoins() const{
    return GetGameState<ACustomGameState>()->CoinNumber;
}

void AGameModeTutorial::IncreaseCoins() {
    GetGameState<ACustomGameState>()->CoinNumber += 1;
}

void AGameModeTutorial::OnLevelLoad() {
    FLatentActionInfo LatentInfo;	
    UGameplayStatics::LoadStreamLevel(this, Levels[LevelContator], true, false, LatentInfo);

    LevelContator += 1;

    if(Levels.Num() > LevelContator){
        ULevelStreaming* Level = UGameplayStatics::GetStreamingLevel(GetWorld(), Levels[LevelContator - 1]);
        Level->OnLevelLoaded.AddDynamic(this,&AGameModeTutorial::OnLevelLoad);
    }
}
