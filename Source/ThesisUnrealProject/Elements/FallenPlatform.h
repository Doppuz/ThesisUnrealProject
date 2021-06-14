// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShakingAbstract.h"
#include "FallenPlatform.generated.h"

UCLASS()
class THESISUNREALPROJECT_API AFallenPlatform : public AShakingAbstract
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFallenPlatform();

#pragma region Components

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAcces = true))
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAcces = true))
	UStaticMeshComponent* PlatformMesh;	

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAcces = true))
	class UBoxComponent* PlatformCollider;	

#pragma endregion

	UPROPERTY(EditAnywhere, Category = "Movement")
	float Speed;

	//Boolean needed to choose the moment when falling the platform.
	bool bFall;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ShakingActor(float DeltaTime) override;

	//To avoid to move the platform in the start position.
	bool bIsFallen;

	FTimerHandle FallenTimer;

	void StartFalling();

private:
	
	UFUNCTION()    
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};
