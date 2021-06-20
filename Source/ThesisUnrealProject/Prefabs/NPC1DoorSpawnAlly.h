// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Character/PawnInteractiveClass.h"
#include "NPC1DoorSpawnAlly.generated.h"

class AAICharacterPawnQuad;

UCLASS()
class THESISUNREALPROJECT_API ANPC1DoorSpawnAlly : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANPC1DoorSpawnAlly();

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* Triggers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UBoxComponent* Trigger;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere,  Category = "SpawnAlly")
	TSubclassOf<AAICharacterPawnQuad> AllyClass;

	UFUNCTION()
	void LeftChoiceEvent();
	
	UFUNCTION()
	void RightChoiceEvent();
	
	UFUNCTION()
	void EndChoiceEvent(APawnInteractiveClass* SpokenActor);

	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit);

	bool bLeftChoice;
	bool bRightChoice;

};
