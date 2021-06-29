// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class THESISUNREALPROJECT_API AMainMenu : public ALevelScriptActor
{
	GENERATED_BODY()

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

    UUserWidget* CurrentWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
    TSubclassOf<UUserWidget> WidgetClass;
	
};
