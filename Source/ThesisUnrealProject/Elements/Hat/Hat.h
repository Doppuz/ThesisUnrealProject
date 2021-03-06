// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Hat.generated.h"

UCLASS()
class THESISUNREALPROJECT_API AHat : public AActor{

	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHat();

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	//Only because I can't serialize pointers
	UPROPERTY(EditAnywhere)
	int HatID;

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHatOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
