// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AIBull.generated.h"

UCLASS()
class THESISUNREALPROJECT_API AAIBull : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAIBull();

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = General)
	class UBoxComponent* Collider;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = General)
	UStaticMeshComponent* Mesh;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = Camera)
	class USpringArmComponent* CameraArmComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = Camera)
	class UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = General)
	class UFloatingPawnMovement* PawnMovement;

	float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere)
	float Damage;

	UPROPERTY(EditAnywhere)
	float MaxHealth;

	UPROPERTY(VisibleAnywhere)
	float CurrentHealth;



};
