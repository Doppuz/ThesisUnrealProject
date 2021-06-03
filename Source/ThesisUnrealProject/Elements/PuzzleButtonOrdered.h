// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleButton.h"
#include "PuzzleButtonOrdered.generated.h"

UCLASS()
class THESISUNREALPROJECT_API APuzzleButtonOrdered : public APuzzleButton
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuzzleButtonOrdered();

	void OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit) override;

};
