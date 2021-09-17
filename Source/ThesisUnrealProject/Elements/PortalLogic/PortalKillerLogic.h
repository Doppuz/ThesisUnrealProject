// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PortalKillerLogic.generated.h"

class APortal;
class ARoomKiller;
class ADoor;

UCLASS()
class THESISUNREALPROJECT_API APortalKillerLogic : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APortalKillerLogic();

	UPROPERTY(EditAnywhere)
	APortal* StartPortal;

	APortal* EndPortal;

	UPROPERTY(EditAnywhere)
	ARoomKiller* RoomKiller;

	UPROPERTY(EditAnywhere)
	ADoor* Door;

	TSubclassOf<APortal> PortalClass;
	FVector PortalStartPos;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UFUNCTION()
	void OpenDoor();
};
