// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "CustomGameState.h"
#include "GameModeAbstract.h"
#include "GameModeTutorial.generated.h"

class APuzzleButton;
class ADoor;
class ATriggerVolume;


UCLASS()
class THESISUNREALPROJECT_API AGameModeTutorial : public AGameModeAbstract
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameModeTutorial();
	
//--------- Coins ---------
	
	int GetCoins() const;
	void IncreaseCoins();


// ---------- Level loaded ------------

	TArray<FName> Levels;

	UFUNCTION()
	void OnLevelLoad();

	//Used when I load the level after using a Checkpoint.
	int LevelContator = 0;

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};
