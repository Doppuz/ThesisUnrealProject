// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Crate.generated.h"

UCLASS()
class THESISUNREALPROJECT_API ACrate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACrate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAcces = true))
	USceneComponent* Root;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAcces = true))
	class UDestructibleComponent* CrateMesh;	

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAcces = true))
	class UBoxComponent* BoxCollider;	


};
