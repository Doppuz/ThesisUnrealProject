// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "CustomGameState.h"
#include "GameModeTutorial.generated.h"

class APuzzleButton;
class ADoor;
class ATriggerVolume;


UCLASS()
class THESISUNREALPROJECT_API AGameModeTutorial : public AGameModeBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameModeTutorial();

	/** Remove the current menu widget and create a new one from the specified class, if provided. */
    UFUNCTION(BlueprintCallable, Category = "UMG Game")
    void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);/** Remove the current menu widget and create a new one from the specified class, if provided. */

	/** The widget class we will use as our dialog menu. */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
    TSubclassOf<UUserWidget> WidgetClass;

	UUserWidget* GetCurrentWidgetUI();

//--------- Coins ---------
	
	int GetCoins() const;
	void IncreaseCoins();


// ---------- Level loaded ------------

	TArray<FName> Levels;

	UFUNCTION()
	void OnLevelLoad();

	//Used when I load the level after using a Checkpoint.
	int LevelContator = 1;

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    UUserWidget* CurrentWidget;


};
