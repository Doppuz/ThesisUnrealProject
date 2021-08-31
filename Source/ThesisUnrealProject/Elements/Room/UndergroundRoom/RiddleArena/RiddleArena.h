// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../GeneralUndergroundRoom.h"
#include "RiddleArena.generated.h"

class ADoor;
class ARiddleNPC;

UCLASS()
class THESISUNREALPROJECT_API ARiddleArena : public AGeneralUndergroundRoom
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, Category = "Elements")
	TSubclassOf<ADoor> DoorClass;

	UPROPERTY(EditAnywhere, Category = "Elements")
	TSubclassOf<ARiddleNPC> RiddleNpcClass;

	void GenerateRiddleDoors();

	UFUNCTION()
	void OpenRiddleDoor(ARiddleNPC* RiddleActor);

	UFUNCTION()
	void EndDialog(APawnInteractiveClass* SpokenActor);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
