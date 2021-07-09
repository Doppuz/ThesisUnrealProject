// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnemyAIAbstract.h"

#include "AIShotPawnObstacle.generated.h"

class AGunController;
class ASquaredProjectile;

UCLASS()
class THESISUNREALPROJECT_API AAIShotPawnObstacle : public APawn{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAIShotPawnObstacle();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = General)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = Camera)
	USpringArmComponent* CameraArmComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = Camera)
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = General)
	class UBoxComponent* Collider;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = General)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = General)
	UStaticMeshComponent* EquipmentMesh;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = General)
	USceneComponent* ProjectileSpawnPosition;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = General)
	UBoxComponent* TriggerLeft;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = General)
	UBoxComponent* TriggerRight;

	//MovementParameters
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Movement)
	float MovementSpeed;

	//Projectile class
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Projectile)
	TSubclassOf<ASquaredProjectile> ProjectileClass;
	
	//Time between 2 projectile
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Projectile)
	float ProjectileTimeout;
	
	void Shoot();

	//Used to move the cannon in the obstacle of puzzle 3.
	UPROPERTY(EditAnywhere, Category = "AI")
	bool bStationary;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit);

	//Shot
	bool bAmIShooting;
	FTimerHandle ShotTimer;
	
};
