// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

class APuzzleButton;
class APawnInteractiveClass;

UCLASS()
class THESISUNREALPROJECT_API ADoor : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ADoor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	USceneComponent* Root;
	
	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	class UBoxComponent* Collider;

	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* DoorMesh;

	//True when I want to open/close the door.
	bool bOpenDoor;

	UPROPERTY(EditAnywhere, Category = "Opening")
	bool bClose;
	
	UPROPERTY(EditAnywhere, Category = "Opening")
	float Speed;
	
	UPROPERTY(EditAnywhere, Category = "Opening")
	float Distance;

	UPROPERTY(EditAnywhere, Category = "Opening")
	int ID;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	FVector FinalPosition;


};
