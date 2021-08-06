// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Character/AllyAI/PawnInteractiveClass.h"
#include "NPC1Door2.generated.h"

UCLASS()
class THESISUNREALPROJECT_API ANPC1Door2 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANPC1Door2();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* NPCs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UChildActorComponent* NPC1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* Doors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UChildActorComponent* Door1;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Equipment)
	UStaticMesh* MeshToEquip;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = AttackSpeed)
	bool bIncreaseAttackSpeed;

	UFUNCTION()
	void LeftChoiceEvent();
	
	UFUNCTION()
	void RightChoiceEvent();
	
	UFUNCTION()
	void EndChoiceEvent(APawnInteractiveClass* SpokenActor);

	bool bLeftChoice;
	bool bRightChoice;

};
