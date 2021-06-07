// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovablePlatform.generated.h"

UCLASS()
class THESISUNREALPROJECT_API AMovablePlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovablePlatform();

#pragma region Components

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAcces = true))
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAcces = true))
	UStaticMeshComponent* PlatformMesh;	

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAcces = true))
	class UBoxComponent* PlatformCollider;	

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAcces = true))
	USceneComponent* Triggers;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAcces = true))
	UBoxComponent* FirstBox;	

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAcces = true))
	UBoxComponent* SecondBox;

#pragma endregion

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	bool bHorizontalMovement;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float Speed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit);


};
