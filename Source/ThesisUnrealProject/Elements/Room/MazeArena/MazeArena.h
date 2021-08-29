// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../GeneralRoomWithDoor.h"
#include "MazeArena.generated.h"

class AMazeManager;
class APuzzleButton;

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

	void SetMazeLocation(FVector);

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	AMazeManager* MazeManager;

};
