// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../GeneralUndergroundRoom.h"
#include "MazeArena.generated.h"

class AMazeManager;
class APuzzleButton;
class ATriggerSpawnNight;
class AStair;
class AMazeCell2;
class APortal;

/**
 * 
 */
UCLASS()
class THESISUNREALPROJECT_API AMazeArena : public AGeneralUndergroundRoom{

	GENERATED_BODY()

public:

	//Class for puzzle button spawn.
	UPROPERTY(EditAnywhere, Category = "Elements")
	TSubclassOf<APuzzleButton> PuzzleButtonClass;

	UPROPERTY(EditAnywhere, Category = "Elements")
	TSubclassOf<ATriggerSpawnNight> TriggerNightClass;
	
	TArray<ATriggerSpawnNight*> Triggers;
	APuzzleButton* Button;

	virtual void OpenDoor() override;

	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit);

	UFUNCTION()
	void OnOverlapPortal(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit);

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};
