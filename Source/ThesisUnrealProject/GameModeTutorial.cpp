// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeTutorial.h"
#include "Elements/Puzzle/PuzzleButton.h"
#include "Elements/GeneralElements/Doors/Door.h"
#include "Kismet/GameplayStatics.h"
#include "UI/UIWidgetDialog.h"
#include "UI/Elements/UIBox.h"
#include "CustomGameState.h"
#include "Engine/TriggerVolume.h"
#include "CheckPoints/SaveGameData.h"
#include "CustomGameState.h"
#include "Engine/LevelStreaming.h"
#include "Character/CharacterPawnQuad.h"

AGameModeTutorial::AGameModeTutorial() {
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AGameModeTutorial::BeginPlay() {
    
    Super::BeginPlay();

	UUIWidgetDialog* DialogWidget = Cast<UUIWidgetDialog>(CurrentWidget);
    DialogWidget->HideSizeBox();
    DialogWidget->TextBox->BoxContainer->Visibility = ESlateVisibility::Hidden;

    ACharacterPawnQuad* MyPawn = Cast<ACharacterPawnQuad>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
    MyPawn->StopCharacter(false);
    
    UGameplayStatics::GetPlayerController(GetWorld(),0)->SetInputMode(FInputModeGameOnly());

    //if(MyPawn != nullptr)
    //    Cast<APlayerController>(MyPawn->GetController())->SetPause(true);

    // Retrieve and cast the USaveGame object to UMySaveGame.
    if (USaveGameData* LoadedGame = Cast<USaveGameData>(UGameplayStatics::LoadGameFromSlot("Checkpoint", 0))){
        
        // The operation was successful, so LoadedGame now contains the data we saved earlier.
        // Load the position only if I don't come from the main menu.
        if(LoadedGame->PlayerLocation != FVector(0.f,0.f,900000.22f))
            MyPawn->SetActorLocation(LoadedGame->PlayerLocation);

        //Load the bartle's type data.
        Update->Types[Type::Achiever] = LoadedGame->Achiever;
        Update->Types[Type::Explorer] = LoadedGame->Explorer;
        Update->Types[Type::Killer] = LoadedGame->Killer;
        Update->Types[Type::Socializer] = LoadedGame->Socializer;

        Update->TypesQuestionary[Type::Achiever] = LoadedGame->AchieverQ;
        Update->TypesQuestionary[Type::Explorer] = LoadedGame->ExplorerQ;
        Update->TypesQuestionary[Type::Killer] = LoadedGame->KillerQ;
        Update->TypesQuestionary[Type::Socializer] = LoadedGame->SocializerQ;

        //Load levels
        Levels = LoadedGame->Levels;

        //Character characteristics
        if(LoadedGame->AttackSpeed != 0.f)
            MyPawn->ProjectileTimeout = LoadedGame->AttackSpeed ;
		
        MyPawn->EquipmentMesh->SetStaticMesh(LoadedGame->Hat);
  
        if(Levels.Num() != 0){
            FLatentActionInfo LatentInfo;	
            UGameplayStatics::LoadStreamLevel(this, Levels[0], true, false, LatentInfo);
            
            ULevelStreaming* Level = UGameplayStatics::GetStreamingLevel(GetWorld(), Levels[0]);
            Level->OnLevelLoaded.AddDynamic(this,&AGameModeTutorial::OnLevelLoad);

            LevelContator += 1;

        }

    }else{
        
        if(Levels.Num() != 0){
            FLatentActionInfo LatentInfo;	
            UGameplayStatics::LoadStreamLevel(this, Levels[0], true, false, LatentInfo);
            
            ULevelStreaming* Level = UGameplayStatics::GetStreamingLevel(GetWorld(), Levels[0]);
            Level->OnLevelLoaded.AddDynamic(this,&AGameModeTutorial::OnLevelLoad);

            LevelContator += 1;

        }

        /*ULevelStreaming* Level = UGameplayStatics::GetStreamingLevel(GetWorld(), "FirstPuzzle");
        Level->OnLevelLoaded.AddDynamic(this,&AGameModeTutorial::OnLevelLoad);

        Levels.Add("FirstPuzzle");*/

    }

}

//--- Get and Set for the coins

int AGameModeTutorial::GetCoins() const{
    return GetGameState<ACustomGameState>()->CoinsNumber;
}

void AGameModeTutorial::IncreaseCoins() {
    GetGameState<ACustomGameState>()->CoinsNumber += 1;
}

void AGameModeTutorial::OnLevelLoad() {
    if(Levels.Num() > LevelContator){
    
        FLatentActionInfo LatentInfo;	
        UGameplayStatics::LoadStreamLevel(this, Levels[LevelContator], true, false, LatentInfo);

        ULevelStreaming* Level = UGameplayStatics::GetStreamingLevel(GetWorld(), Levels[LevelContator]);
        Level->OnLevelLoaded.AddDynamic(this,&AGameModeTutorial::OnLevelLoad);
 
        LevelContator += 1;
        
    }else{
        
        GetWorld()->GetTimerManager().SetTimer(StartTimer, this, &AGameModeTutorial::StopGame, 0.5, false);

    }
}

void AGameModeTutorial::StopGame(){

	ACharacterPawnQuad* Player = Cast<ACharacterPawnQuad>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
    Player->StopCharacter(true);

}
