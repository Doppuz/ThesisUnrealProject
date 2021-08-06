// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RumbleArena.h"
#include "RumbleArenaWithDoor.generated.h"

class ADoor;

UCLASS()
class THESISUNREALPROJECT_API ARumbleArenaWithDoor : public ARumbleArena{

	GENERATED_BODY()

public:

	//Door to be opened after the arena is complited
	ADoor* Door;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UFUNCTION()
	void OpenDoor();

};
