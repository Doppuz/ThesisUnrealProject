// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ShakingAbstract.h"
#include "CoreMinimal.h"
#include "RiddleTemplate.generated.h"

class APuzzleButton;
class APawnInteractiveClass;
class AEnemyAIAbstract;

UCLASS(Abstract)
class THESISUNREALPROJECT_API ARiddleTemplate : public AShakingAbstract
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARiddleTemplate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	//check Puzzle actors overlap.
	virtual void CheckPuzzleActor();

	//check Ally actors condition.
	virtual void CheckAllyActor();

	//check Ally actors condition.
	virtual void CheckEnemyActor();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//check if the puzzle is solved
	bool bSolved;

	//Actor to check if it is solved.
	UPROPERTY(EditAnywhere, Category = "Opening")
	ARiddleTemplate* ComplementaryActor;

	//If all Puzzle actors are overlapped, the door opens.
	UPROPERTY(EditAnywhere, Category = "OpenConditions")
	TArray<APuzzleButton*> PuzzleActivator;

	//If I have spoken with all the Ally actors, the door opens.
	UPROPERTY(EditAnywhere, Category = "OpenConditions")
	TArray<APawnInteractiveClass*> AllyActivator;

	//If I have killed all the enemy actors, the door opens.
	UPROPERTY(EditAnywhere, Category = "OpenConditions")
	TArray<AEnemyAIAbstract*> EnemyActivator;

	//If I am in the arena I need to delete all the enemies before opening the door.
	UPROPERTY(EditAnywhere, Category = "OpenConditions")
	bool bUseTurnMethodology;

};
