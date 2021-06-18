// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Character/PawnInteractiveClass.h"
#include "NPC1Door.generated.h"

UCLASS()
class THESISUNREALPROJECT_API ANPC1Door : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANPC1Door();

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

#pragma region NPC
		
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Speak)
	TArray<FString> Speech;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Speak)
	TArray<FQuestion> Questions;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Speak)
	int QuestionAt;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Equipment)
	UStaticMesh* MeshToEquip;

#pragma endregion

	UFUNCTION()
	void LeftChoiceEvent();
	
	UFUNCTION()
	void RightChoiceEvent();
	
	UFUNCTION()
	void EndChoiceEvent();

};
