// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "GameModeTutorial.generated.h"

class APuzzleButton;
class ADoor;
class ATriggerVolume;
/**
 * 
 */
UCLASS()
class THESISUNREALPROJECT_API AGameModeTutorial : public AGameModeBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameModeTutorial();

	virtual void Tick(float DeltaTime) override;

	//Puzzle1 (Choice 1)
	void CheckPuzzle1(APuzzleButton*);
	void ResetPuzzle1();
	bool bSolvedPuzzle1;
	bool bGateDestroyed;

	//Gate 2
	bool bEnemyDefeated;	
	bool bLeft;

	//Puzzle 2
	void CheckPuzzle2(int);

	/** Remove the current menu widget and create a new one from the specified class, if provided. */
    UFUNCTION(BlueprintCallable, Category = "UMG Game")
    void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);/** Remove the current menu widget and create a new one from the specified class, if provided. */

	/** The widget class we will use as our dialog menu. */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
    TSubclassOf<UUserWidget> WidgetClass;

	UUserWidget* GetCurrentWidgetUI();

	//Doors to be opened.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Doors")
    TArray<AActor*> DoorActors;

	//Open the door with the number passed as parameter.
	void SetDoorOpen(int);

	//Trigger volumes.
	TArray<AActor*> TriggerVolumes;

//--------- Coins ---------
	
	int GetCoins() const;
	void IncreaseCoins();

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    UUserWidget* CurrentWidget;

private:

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = "true"), Category = Materials)
	UMaterial* GreyColor;
	
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = "true"), Category = Materials)
	UMaterial* RedColor;
	
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = "true"), Category = Materials)
	UMaterial* GreenColor;

	//Puzzle1
	TArray<APuzzleButton*> ElemsPuzzle1;

	//Puzzle2
	TArray<int> ElemsPuzzle2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"), Category = Door)
	TSubclassOf<ADoor> DoorClass;

	//Timers
	FTimerHandle ResetPuzzle1Timer;
};
