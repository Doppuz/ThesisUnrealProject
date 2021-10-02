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
#include "../InterfaceMovableAI.h"

#include "PawnInteractiveMove.generated.h"

class ASquaredProjectile;
class UFloatingPawnMovement;

UCLASS()
class THESISUNREALPROJECT_API APawnInteractiveMove : public APawnInteractiveClass, public IInterfaceMovableAI{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APawnInteractiveMove();

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = Camera)
	USpringArmComponent* CameraArmComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = Camera)
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = General)
	UStaticMeshComponent* EquipmentMesh;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = General)
	USceneComponent* ProjectileSpawnPosition;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = General)
	UFloatingPawnMovement* PawnMovement;

	//Projectile class
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Projectile)
	TSubclassOf<ASquaredProjectile> ProjectileClass;

	//Time between 2 projectile
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Projectile)
	float ProjectileTimeout;

	virtual void SetInitialValue(FVector Pos, int Contator, bool Direction, bool SameDirection) override;

//---- General ---
	void Choice(int) override;

//---- StartInteraction
	void StartInteraction() override;
	void EndInteraction() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	//InteractiveActor
	APawnInteractiveClass* InteractiveActor;

};
