// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleTemplate.generated.h"

UCLASS()
class THESISUNREALPROJECT_API APuzzleTemplate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuzzleTemplate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//check if the puzzle is solved
	bool bSolved;

	//Actor to check if it is solved.
	UPROPERTY(EditAnywhere, Category = "Opening")
	APuzzleTemplate* ComplementaryActor;

	

};
