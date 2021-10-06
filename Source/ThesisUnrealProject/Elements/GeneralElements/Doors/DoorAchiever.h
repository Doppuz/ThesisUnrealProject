// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Door.h"
#include "DoorAchiever.generated.h"

class AEnemyAIAbstract;
class AGenericDestructibleElements;
class AKeyActor;

UCLASS()
class THESISUNREALPROJECT_API ADoorAchiever : public ADoor{

	GENERATED_BODY()
	
public:

	ADoorAchiever();

	UPROPERTY(VisibleAnywhere)
	USceneComponent* SpawnPos0;
	
	UPROPERTY(VisibleAnywhere)
	USceneComponent* SpawnPos1;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* SpawnPos2;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* SpawnPos3;
	
	UPROPERTY(VisibleAnywhere)
	USceneComponent* SpawnPos4;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	TArray<TSubclassOf<AEnemyAIAbstract>> Enemies;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	TArray<TSubclassOf<AGenericDestructibleElements>> DestrElem;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<AKeyActor> KeyClass;
	
	TArray<AGenericDestructibleElements*> DestrActors;

	int KeyPos;

	UFUNCTION()
	void SpawnKey(AActor* Elem);

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
