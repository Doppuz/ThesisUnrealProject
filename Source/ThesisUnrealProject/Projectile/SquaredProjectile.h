// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SquaredProjectile.generated.h"

UCLASS()
class THESISUNREALPROJECT_API ASquaredProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASquaredProjectile();

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "General")
	class UBoxComponent* Collider;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "General")
	UStaticMeshComponent* Mesh;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "General")
	class UProjectileMovementComponent* MovementProjectile;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Damage")
	float Damage;

	AActor* MyOwner;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private: 
	
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit);

};
