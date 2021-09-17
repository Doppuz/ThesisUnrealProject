// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PortalExplorerLogic.generated.h"

class APuzzleButton;
class APortal;
class AMazeManager;
class ADoor;

UCLASS()
class THESISUNREALPROJECT_API APortalExplorerLogic : public AActor{

	GENERATED_BODY()

public:	

	UPROPERTY(EditAnywhere)
	APuzzleButton* Button;

	UPROPERTY(EditAnywhere)
	APortal* StartPortal;

	APortal* EndPortal;

	UPROPERTY(EditAnywhere)
	AMazeManager* MazeManager;

	UPROPERTY(EditAnywhere)
	ADoor* Door;

	TSubclassOf<APortal> PortalClass;

	FVector PortalStartPos;

	// Sets default values for this actor's properties
	APortalExplorerLogic();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UFUNCTION()
	void OpenDoorPuzzle(APuzzleButton* Elem);

	UFUNCTION()
	void OnOverlapPortal(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit);


};
