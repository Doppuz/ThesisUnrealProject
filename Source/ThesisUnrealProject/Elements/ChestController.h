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
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:


	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = "true"))
	USceneComponent* Root;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = "true"))
	class UCapsuleComponent* ChestCollider;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* ChestMesh;

};
