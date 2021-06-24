// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CubeLevel.generated.h"

UCLASS()
class THESISUNREALPROJECT_API ACubeLevel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACubeLevel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	class UBoxComponent* Collider;

	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;
	
};
