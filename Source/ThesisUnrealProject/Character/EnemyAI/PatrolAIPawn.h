// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PatrolAIPawn.generated.h"

UCLASS()
class THESISUNREALPROJECT_API APatrolAIPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APatrolAIPawn();

#pragma region Components

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = General)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = General)
	class UBoxComponent* Collider;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = General)
	class UCapsuleComponent* CapsuleTrigger;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = General)
	UBoxComponent* FirstTrigger;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = General)
	UBoxComponent* SecondTrigger;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = General)
	class USpotLightComponent* SpotLight;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = General)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = Camera)
	class USpringArmComponent* CameraArmComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = Camera)
	class UCameraComponent* CameraComponent;

#pragma endregion Components



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = Speed)
	float Speed;

	float CurrentSpeed;

private:

	FTimerHandle TimerStop;

	void StopMovement();
	void StartMovement();

#pragma region OnComponentEvent

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit);

	UFUNCTION()
	void OnOverlapTrigger(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit);

#pragma endregion OnComponentEvent
	

};
