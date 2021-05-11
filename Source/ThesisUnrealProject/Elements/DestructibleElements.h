// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestructibleElements.generated.h"

UCLASS()
class THESISUNREALPROJECT_API ADestructibleElements : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADestructibleElements();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Destruction")
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Destruction")
	class UDestructibleComponent* DestructibleMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "General")
	int ID;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UFUNCTION()
	void OnComponentFracture(const FVector& HitPoint, const FVector& HitDirection);

};
