// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Door.h"
#include "DoorExplorer.generated.h"

class APuzzleButton;

UCLASS()
class THESISUNREALPROJECT_API ADoorExplorer : public ADoor{

	GENERATED_BODY()

public:

	ADoorExplorer();
	
	UPROPERTY(VisibleAnywhere)
	USceneComponent* SpawnPos1;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* SpawnPos2;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* SpawnPos3;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<APuzzleButton> PuzzleClass;

	UPROPERTY(EditAnywhere, Category = "Materials")
	UMaterial* RedColor;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:

	TArray<APuzzleButton*> PuzzleActors;

	TArray<APuzzleButton*> MyPuzzleOrder;

	void Shuffle();

	UFUNCTION()
	void PuzzleOverlap(APuzzleButton* Elem);

	FTimerHandle ResetPuzzleTimer;

	void ResetPuzzle();

};
