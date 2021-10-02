// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EnemyAIAbstract.h"
#include "AIBull.generated.h"

UCLASS()
class THESISUNREALPROJECT_API AAIBull : public AEnemyAIAbstract{
	
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

	//Health Bar
	UPROPERTY( VisibleAnywhere )
	class UWidgetComponent* HealthWidgetComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere)
	float Damage;

};
