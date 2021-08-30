// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../GeneralRoomWithDoor.h"
#include "MazeArena.generated.h"

class AMazeManager;
class APuzzleButton;
class ATriggerSpawnNight;

/**
 * 
 */
UCLASS()
class THESISUNREALPROJECT_API AMazeArena : public AGeneralRoomWithDoor{

	GENERATED_BODY()

public:

	AMazeArena();

	//Maze to be spawned
	UPROPERTY(EditAnywhere, Category = "Elements")
	TSubclassOf<AMazeManager> MazeManagerClass;

	//Class for puzzle button spawn.
	UPROPERTY(EditAnywhere, Category = "Elements")
	TSubclassOf<APuzzleButton> PuzzleButtonClass;

	UPROPERTY(EditAnywhere, Category = "Elements")
	TSubclassOf<ATriggerSpawnNight> TriggerNightClass;

	ADoor* RoomDoor;
	TArray<ATriggerSpawnNight*> Triggers;

	void SetMazeLocation(FVector);
	FVector GetMazeLocation();
	FVector GetMazeInstanceLocation(int);

	void SetMazeRotation(FRotator);

	virtual void OpenDoor() override;

	void CreateNightTrigger(FTransform);
	
	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit);

	AMazeManager* MazeManager;
	
protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};
