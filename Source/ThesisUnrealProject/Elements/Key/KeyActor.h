// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KeyActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FKeyCollectedDelegate);

UCLASS()
class THESISUNREALPROJECT_API AKeyActor : public AActor{

	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKeyActor();

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	FKeyCollectedDelegate KeyDelegate;

	UFUNCTION()
	void OnKeyOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit);

	UPROPERTY(EditAnywhere)
	float RotationSpeed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
