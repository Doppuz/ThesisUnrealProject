// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MazeManager.h"
#include "SocializerMaze.generated.h"

class ARiddleNPC;
class APawnInteractiveClass;
class ADoorRiddle;

UCLASS()
class THESISUNREALPROJECT_API ASocializerMaze : public AMazeManager{

	GENERATED_BODY()

public:

	ASocializerMaze();

	UPROPERTY(EditAnywhere, Category = "Elements")
	TSubclassOf<ADoorRiddle> DoorRiddle;

	//Maze's Door
	ADoor* ExternalDoor;

	FVector StartPortalPos;

	FVector MazeActorPos;

	void GenerateRiddleDoors();

	UFUNCTION()
	void OpenDoor(ARiddleNPC* RiddleActor);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
