// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "../../Character/InterfaceMovableAI.h"
#include "Storm.generated.h"

UCLASS()
class THESISUNREALPROJECT_API AStorm : public APawn, public IInterfaceMovableAI{

	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	AStorm();
	
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* Collider;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* Particles;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	int CurrentIndex;

	UPROPERTY(EditAnywhere)
	bool StraightDirection;

	UPROPERTY(EditAnywhere)
	float Speed;

	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit);

};
