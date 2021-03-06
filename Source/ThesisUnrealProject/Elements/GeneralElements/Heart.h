// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Heart.generated.h"

UCLASS()
class THESISUNREALPROJECT_API AHeart : public AActor{

	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHeart();

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	float RotationSpeed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnCoinOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
