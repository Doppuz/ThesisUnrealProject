// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "GameModeAbstract.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class THESISUNREALPROJECT_API AGameModeAbstract : public AGameModeBase{

	GENERATED_BODY()

public:

	/** Remove the current menu widget and create a new one from the specified class, if provided. */
    UFUNCTION(BlueprintCallable, Category = "UMG Game")
    void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

	UUserWidget* GetCurrentWidgetUI();

	/** The widget class we will use as our menu when the game starts. */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
    TSubclassOf<UUserWidget> StartingWidgetClass;

	/** The widget instance that we are using as our menu. */
    UPROPERTY()
    UUserWidget* CurrentWidget;

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
