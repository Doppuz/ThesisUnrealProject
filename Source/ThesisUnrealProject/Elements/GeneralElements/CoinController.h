// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CoinController.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCoinCollectedDelegate);

UCLASS()
class THESISUNREALPROJECT_API ACoinController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACoinController();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere)
	int ID;

	// check if it is collected.
	bool bIsCollected;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAcces = true))
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAcces = true))
	UStaticMeshComponent* CoinMesh;	

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAcces = true))
	class USphereComponent* CoinCollider;	

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAcces = true))
	USceneComponent* Triggers;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAcces = true))
	class UBoxComponent* TopBox;	

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAcces = true))
	class UBoxComponent* BotBox;	

	UPROPERTY(EditANywhere, Category = "Rotation", meta = (AllowPrivateAcces = true))
	float RotationValue;

	UPROPERTY(EditANywhere, Category = "UpDownMovement", meta = (AllowPrivateAcces = true))
	float OffSetValue;

// --- Coin collection delegate ---
	FCoinCollectedDelegate CollectedDelegate;

private:

	UFUNCTION()
	void OnBoxOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit);

	UFUNCTION()
	void OnCoinOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit);

};
