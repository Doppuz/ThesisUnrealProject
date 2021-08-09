// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../GeneralRoomWithDoor.h"
#include "RumbleArena.h"
#include "RumbleArenaDoorNpc.generated.h"

class APawnInteractiveClass;

UCLASS()
class THESISUNREALPROJECT_API ARumbleArenaDoorNpc : public ARumbleArena{

	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "Elements")
	TSubclassOf<APawnInteractiveClass> NpcClass;
	
	//Door to be closed after talking with the npc.
	ADoor* RoomDoor;

	//State the beginning of the arena.
	bool bStart = false;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Redefinition of the method to open the room door.
	virtual void OpenDoor();

private:

	UFUNCTION()
	void Start();

	APawnInteractiveClass* InteractiveActor;

};
