// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChestController.generated.h"


UCLASS()
class THESISUNREALPROJECT_API AChestController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChestController();

private:


	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	class UCapsuleComponent* ChestCollider;

	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* ChestMesh;

};
