// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "PawnInteractiveClass.h"
#include "EnemyAIAbstract.h"

#include "CharacterPawnQuad.generated.h"

class AGunController;
class ASquaredProjectile;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEndDelegate);

UCLASS()
class THESISUNREALPROJECT_API ACharacterPawnQuad : public AEnemyAIAbstract{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterPawnQuad();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

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

	//SpotLight
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = Light)
	class USpotLightComponent* SpotLight;

	//MovementParameters
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Movement)
	float MovementSpeed;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Movement)
	float RotationSpeed;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Movement)
	float JumpForce;

	//Projectile class
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Projectile)
	TSubclassOf<ASquaredProjectile> ProjectileClass;
	
	//Time between 2 projectile
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Projectile)
	float ProjectileTimeout;

	void MoveForward(float Axis);
	void MoveRight(float Axis); 
	void RotateYaw(float Axis);
	void RotatePitch(float Axis);
	
	void Jump();
	void SetJump();
	
	void Shoot();
	void SetShooting();
	
	//Stop movement after clicking E.
	bool bStopMovement;

	//Player Mouse Pointer
	void SetMousePointer(bool);

	//Reference to the NPC who I am talking with
	class APawnInteractiveClass* AllyNPC;

	//LineTracing max range
	float MaxRange;

	//AI MaxRandomMovement	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float MaxRandomDistance;

	//Used to move the cannon in the obstacle of puzzle 3.
	UPROPERTY(EditAnywhere, Category = "AI")
	bool bStationary;
	
	//Position of Ally that follows the player
	UPROPERTY(EditAnywhere, Category = "AI")
	USceneComponent* FollowAllyPosition;

	//Health Bar
	UPROPERTY( VisibleAnywhere )
	class UWidgetComponent* HealthWidgetComponent;

// End delegate

	FEndDelegate End;

// Stop Character (Used to disable physics)
	void StopCharacter(bool);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

private:

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit);
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	//Movement
	FVector VectorMovement;

	//Rotation
	FRotator Rotation;
	FRotator CameraRotation;
	FRotator InitialRotation;

	//Jump
	bool bAmIJump;
	FTimerHandle JumpTimer;

	//Shot
	bool bAmIShooting;
	FTimerHandle ShotTimer;

	//InteractiveActor
	APawnInteractiveClass* InteractiveActor;

	//methods to speak with an NPC when I am cole enought to its.
	void Speak();
	
	//Enemy ID
	UPROPERTY(EditAnywhere)
	int ID;

//Invincible Section

	//Parameter to make the character invincible.
	bool bCharacterInvincible;

	//Method to make the character invisible
	void InvisibleAnimation();
	
	//Number of repetition of the above method
	int NumberOfRepetitions;

	//bool to check if the mesh is visible
	bool bIsVisible;

	//Timer for the above method
	FTimerHandle InvisibleTimer;

	
};
