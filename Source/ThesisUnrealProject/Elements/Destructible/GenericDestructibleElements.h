// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GenericDestructibleElements.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGeneralDestructionDelegate,AActor*, Elem);

UCLASS()
class THESISUNREALPROJECT_API AGenericDestructibleElements : public AActor
{
	GENERATED_BODY()
	
public:

	static int IDCounter;

	// Sets default values for this actor's properties
	AGenericDestructibleElements();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Destruction")
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Destruction")
	class UDestructibleComponent* DestructibleMesh;

	bool bIAmDestroyed;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> SpawnActor;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> CoinActor;

	FGeneralDestructionDelegate DestrDelegate;

	UPROPERTY(VisibleANywhere)
	int ID;

	UPROPERTY(EditAnywhere)
	FVector CoinOffset;

	UPROPERTY(EditAnywhere)
	float ForceApplied;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UFUNCTION()
	void OnComponentFracture(const FVector& HitPoint, const FVector& HitDirection);

};
