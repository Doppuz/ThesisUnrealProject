// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MazePopulate.h"
#include "MazePopulateUnderground.generated.h"

class APuzzleButton;

/**
 * Actually you can consider this as the room for the explorer.
 */
UCLASS()
class THESISUNREALPROJECT_API AMazePopulateUnderground : public AMazePopulate{

	GENERATED_BODY()
	
public:

	virtual void DepthVisit(AMazeCell2* Start);

	virtual void AddDoors();

};
