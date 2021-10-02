// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyAIAbstract.h"
#include "AIShooterPawn.generated.h"

class ASquaredProjectile;

/**
 * 
 */
UCLASS()
class THESISUNREALPROJECT_API AAIShooterPawn : public AEnemyAIAbstract{
	
	GENERATED_BODY()

public:

	AAIShooterPawn();

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

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = General)
	USceneComponent* ProjectileSpawnPosition;

	//Health Bar
	UPROPERTY( VisibleAnywhere )
	class UWidgetComponent* HealthWidgetComponent;

	//Projectile class
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Projectile)
	TSubclassOf<ASquaredProjectile> ProjectileClass;

	float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UPROPERTY(EditAnywhere)
	float Damage;

	void Shoot();

};
