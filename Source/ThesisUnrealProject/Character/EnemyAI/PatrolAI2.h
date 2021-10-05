// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "../InterfaceMovableAI.h"
#include "PatrolAI2.generated.h"

UCLASS()
class THESISUNREALPROJECT_API APatrolAI2 : public APawn, public IInterfaceMovableAI
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APatrolAI2();

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
	class USpotLightComponent* SpotLight;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = General)
	class UCapsuleComponent* CapsuleTrigger;

	//Set initial value in the blackboard;
	virtual void SetInitialValue(FVector Pos, int Contator, bool Direction, bool SameDirection) override;

	UPROPERTY(EditAnywhere)
	int StartIndex;

	UPROPERTY(EditAnywhere)
	bool StartDirection;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit);


};
