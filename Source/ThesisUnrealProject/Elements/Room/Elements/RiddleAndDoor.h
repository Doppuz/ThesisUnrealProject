// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RiddleAndDoor.generated.h"

class ADoor;
class ARiddleNPC;

UCLASS()
class THESISUNREALPROJECT_API ARiddleAndDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARiddleAndDoor();

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* RiddleNpcPos;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* DoorPos;

	UPROPERTY(EditAnywhere, Category = "Elements")
	TSubclassOf<ADoor> DoorClass;

	UPROPERTY(EditAnywhere, Category = "Elements")
	TSubclassOf<ARiddleNPC> RiddleNpcClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
