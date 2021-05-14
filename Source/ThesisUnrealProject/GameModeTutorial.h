// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "GameModeTutorial.generated.h"

class APuzzleButton;
class ADoor;
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

	/** Remove the current menu widget and create a new one from the specified class, if provided. */
    UFUNCTION(BlueprintCallable, Category = "UMG Game")
    void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);/** Remove the current menu widget and create a new one from the specified class, if provided. */

	/** The widget class we will use as our dialog menu. */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
    TSubclassOf<UUserWidget> WidgetClass;

	UUserWidget* GetCurrentWidgetUI();

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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"), Category = Door)
	TSubclassOf<ADoor> DoorClass;

	//DoorToOpen (Puzzle 1)
    TArray<AActor*> DoorActors;

	//Timers
	FTimerHandle ResetPuzzle1Timer;
};
