// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../GeneralRoomWithDoor.h"
#include "GeneralUndergroundRoom.generated.h"

class AMazeManager;
class AMazeCell2;
class ADoor;
class AStair;

UCLASS(Abstract)
class THESISUNREALPROJECT_API AGeneralUndergroundRoom : public AGeneralRoomWithDoor{

	GENERATED_BODY()

public:

	//Maze to be spawned
	UPROPERTY(EditAnywhere, Category = "Elements")
	TSubclassOf<AMazeManager> MazeManagerClass;

	UPROPERTY(EditAnywhere, Category = "Elements")
	TSubclassOf<AStair> StairClass;


	ADoor* RoomDoor;
	AMazeManager* MazeManager;

	//RoomCell : First cell inside the room.
	void PositionateRoom(AMazeCell2* RoomCell);

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
