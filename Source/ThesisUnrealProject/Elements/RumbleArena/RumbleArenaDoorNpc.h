// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RumbleArenaWithDoor.h"
#include "RumbleArenaDoorNpc.generated.h"

class APawnInteractiveClass;

UCLASS()
class THESISUNREALPROJECT_API ARumbleArenaDoorNpc : public ARumbleArenaWithDoor{

	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "Elements")
	TSubclassOf<APawnInteractiveClass> NpcClass;

	//State the beginning of the arena.
	bool bStart = false;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UFUNCTION()
	void Start();

};
