// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PuzzleButton.h"
#include "PuzzleButtonPortal.generated.h"

class APortal;
class ADoor;

UCLASS()
class THESISUNREALPROJECT_API APuzzleButtonPortal : public APuzzleButton{

	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	APortal* StartPortal;

	UPROPERTY(EditAnywhere)
	ADoor* Door;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<APortal> PortalClass;

	FVector PortalStartPos;

	FVector EndSpawnPosition; //MazeManager->MaxPath[MazeManager->MaxPath.Num() - 2]->GetActorLocation() - FVector(0.f,0.f,50.f)

	UFUNCTION()
	void OpenDoorPuzzle(APuzzleButton* Elem);

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
