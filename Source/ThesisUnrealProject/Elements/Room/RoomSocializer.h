// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RoomKiller.h"
#include "RoomSocializer.generated.h"

class AAICharacterPawnQuad;

UCLASS()
class THESISUNREALPROJECT_API ARoomSocializer : public ARoomKiller{

	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<AAICharacterPawnQuad> AICharacterPawnQuadClass;

	virtual void Start();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
