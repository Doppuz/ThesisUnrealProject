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

    IncreaseValue = 50.f / 6.f;
}

void AGameModeTutorial::BeginPlay() {

    // Retrieve and cast the USaveGame object to UMySaveGame.
    if (USaveGameData* LoadedGame = Cast<USaveGameData>(UGameplayStatics::LoadGameFromSlot("Checkpoint", 0))){
        
        // The operation was successful, so LoadedGame now contains the data we saved earlier.
        UGameplayStatics::GetPlayerPawn(GetWorld(),0)->SetActorLocation(LoadedGame->PlayerLocation);

        //Load the bartle's type data.
        GetGameState<ACustomGameState>()->Types[Type::Achiever] = LoadedGame->Achiever;
        GetGameState<ACustomGameState>()->Types[Type::Explorer] = LoadedGame->Explorer;
        GetGameState<ACustomGameState>()->Types[Type::Killer] = LoadedGame->Killer;
        GetGameState<ACustomGameState>()->Types[Type::Socializer] = LoadedGame->Socializer;

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

//Change these value in an equally distributed way. (-1 means that I don't want to touch that value).
void AGameModeTutorial::EquallyDistributedUpdate(Type IncreasedType,float IncreasedValue,Type DecreasedType,float DecreasedValue) {
    
    TMap<Type,float>* Map = &GetGameState<ACustomGameState>()->Types;

    if(IncreasedType != -1)
        (*Map)[IncreasedType] += IncreasedValue;

    if(DecreasedType != -1)
        (*Map)[DecreasedType] -= DecreasedValue;


    UE_LOG(LogTemp,Warning,TEXT(""));
    UE_LOG(LogTemp,Warning,TEXT("-------------"));

    UE_LOG(LogTemp,Warning,TEXT(" Achiever: %f"), (*Map)[Type::Achiever]);
    UE_LOG(LogTemp,Warning,TEXT(" Killer: %f"), (*Map)[Type::Killer]);
    UE_LOG(LogTemp,Warning,TEXT(" Explorer: %f"), (*Map)[Type::Explorer]);
    UE_LOG(LogTemp,Warning,TEXT(" Socializer: %f"), (*Map)[Type::Socializer]);
}

void AGameModeTutorial::EquallyDistributedUpdate(Type IncreasedType, Type DecreasedType) {
    TMap<Type,float>* Map = &GetGameState<ACustomGameState>()->Types;

    if(IncreasedType != -1)
        (*Map)[IncreasedType] += IncreaseValue;

    if(DecreasedType != -1)
        (*Map)[DecreasedType] -= IncreaseValue;


    UE_LOG(LogTemp,Warning,TEXT(""));
    UE_LOG(LogTemp,Warning,TEXT("-------------"));

    UE_LOG(LogTemp,Warning,TEXT(" Achiever: %f"), (*Map)[Type::Achiever]);
    UE_LOG(LogTemp,Warning,TEXT(" Killer: %f"), (*Map)[Type::Killer]);
    UE_LOG(LogTemp,Warning,TEXT(" Explorer: %f"), (*Map)[Type::Explorer]);
    UE_LOG(LogTemp,Warning,TEXT(" Socializer: %f"), (*Map)[Type::Socializer]);
}

void AGameModeTutorial::DistributedUpdate(Type IncreasedType, Type DecreasedType) {
    
    TMap<Type,float>* Map = &GetGameState<ACustomGameState>()->Types;

    /*if((*Map)[IncreasedType] < (*Map)[DecreasedType]){
    
        if(IncreasedType != -1)
            (*Map)[IncreasedType] += (IncreaseValue + IncreaseValue / 2);

        if(DecreasedType != -1)
            (*Map)[DecreasedType] -= IncreaseValue / 2 ;

    }else if ((*Map)[IncreasedType] > (*Map)[DecreasedType]){
        
        if(IncreasedType != -1)
            (*Map)[IncreasedType] += IncreaseValue / 2;

        if(DecreasedType != -1)
            (*Map)[DecreasedType] -= (IncreaseValue + IncreaseValue / 2);

    }else{
        EquallyDistributedUpdate(IncreasedType, DecreasedType);
        return;
    }*/

    if(IncreasedType != -1)
        (*Map)[IncreasedType] += IncreaseValue;

    if(DecreasedType != -1)
        (*Map)[DecreasedType] -= IncreaseValue;

    UE_LOG(LogTemp,Warning,TEXT(""));
    UE_LOG(LogTemp,Warning,TEXT("-------------"));

    UE_LOG(LogTemp,Warning,TEXT(" Achiever: %f"), (*Map)[Type::Achiever]);
    UE_LOG(LogTemp,Warning,TEXT(" Killer: %f"), (*Map)[Type::Killer]);
    UE_LOG(LogTemp,Warning,TEXT(" Explorer: %f"), (*Map)[Type::Explorer]);
    UE_LOG(LogTemp,Warning,TEXT(" Socializer: %f"), (*Map)[Type::Socializer]);
}

TMap<Type,float> AGameModeTutorial::GetBartleTypes() {
    
    return GetGameState<ACustomGameState>()->Types;

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
