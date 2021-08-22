// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Stair.generated.h"

UCLASS()
class THESISUNREALPROJECT_API AStair : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStair();

	UPROPERTY(VisibleAnywhere)
	UInstancedStaticMeshComponent* Instance;

	UPROPERTY(EditAnywhere)
	float StepsNumber;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
