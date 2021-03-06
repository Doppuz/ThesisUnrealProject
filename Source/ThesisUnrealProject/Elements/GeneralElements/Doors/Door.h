// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

UCLASS()
class THESISUNREALPROJECT_API ADoor : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ADoor();

	static int IDCount;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* DoorMesh;

	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* SubDoorLeftMesh;

	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* SubDoorRightMesh;

	//True when I want to open/close the door.
	UPROPERTY(EditAnywhere)
	bool bOpenDoor;

	UPROPERTY(EditAnywhere, Category = "Opening")
	bool bClose;
	
	UPROPERTY(EditAnywhere, Category = "Opening")
	float Speed;
	
	UPROPERTY(EditAnywhere, Category = "Opening")
	float Distance;

	UPROPERTY(VisibleAnywhere, Category = "Opening")
	int ID;

	void SetDoorDirection(bool);

	UFUNCTION()
	void OpenDoor();

	bool bCheckpoint = false;
	
	FVector FinalPosition;

	FRotator LeftRotation;
	FRotator RightRotation;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FRotator Rot1;
	FRotator Rot2;

};
