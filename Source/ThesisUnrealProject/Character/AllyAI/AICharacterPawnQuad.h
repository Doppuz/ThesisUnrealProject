// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../EnemyAI/AIShooterPawn.h"
#include "../EnemyAI/EnemyAIAbstract.h"
#include "AICharacterPawnQuad.generated.h"

/**
 * 
 */
UCLASS()
class THESISUNREALPROJECT_API AAICharacterPawnQuad : public AAIShooterPawn{

	GENERATED_BODY()

public:

	AAICharacterPawnQuad();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Position of Ally that follows the player
	UPROPERTY(EditAnywhere, Category = "AI")
	UBoxComponent* EnemyInRangeTrigger;

	TArray<AActor*> Enemies;
	TArray<AActor*> UnSortedEnemies;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

private:
	
	UFUNCTION()
	void OnBeginTriggerOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit);

	UFUNCTION()
	void OnEndTriggerOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
