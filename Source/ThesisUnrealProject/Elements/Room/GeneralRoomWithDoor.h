// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneralRoomWithDoor.generated.h"

class ADoor;

UCLASS()
class THESISUNREALPROJECT_API AGeneralRoomWithDoor : public AActor{

	GENERATED_BODY()

public:

	AGeneralRoomWithDoor();

	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	class UBoxComponent* Collider;

	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;

	//Door to be opened after the arena is completed
	ADoor* Door;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OpenDoor();

};
