// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../GeneralRoomWithDoor.h"
#include "GeneralUndergroundRoom.generated.h"

class AMazeManager;
class AMazeCell2;
class ADoor;
class AStair;
class APortal;

UCLASS(Abstract)
class THESISUNREALPROJECT_API AGeneralUndergroundRoom : public AGeneralRoomWithDoor{

	GENERATED_BODY()

public:

	AGeneralUndergroundRoom();
	
	UPROPERTY(VisibleAnywhere)
	USceneComponent* SpawnPortalPosition;

	//Maze to be spawned
	UPROPERTY(EditAnywhere, Category = "Elements")
	TSubclassOf<AMazeManager> MazeManagerClass;

	UPROPERTY(EditAnywhere, Category = "Elements")
	TSubclassOf<APortal> PortalClass;

	APortal* StartPortal;
	APortal* EndPortal;
	AMazeManager* MazeManager;

	FVector PortalPosition;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
