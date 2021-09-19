// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Door.h"
#include "DoorRiddle.generated.h"

class ARiddleNPC;

UCLASS()
class THESISUNREALPROJECT_API ADoorRiddle : public ADoor{

	GENERATED_BODY()
	
public:

	ADoorRiddle();

	UPROPERTY(VisibleAnywhere)
	USceneComponent* SpawnPos1;

	UPROPERTY(EditAnywhere, Category = "Elements")
	TSubclassOf<ARiddleNPC> RiddleNpcClass;

	ARiddleNPC* NPC;

	//Pointers to the maze manager class.
	TArray<TArray<FString>>* Speech;
	TArray<TArray<FString>>* Questions;

	TArray<TArray<FString>>* OldSpeech;
	TArray<TArray<FString>>* OldQuestions;

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	int ShuffleArray(TArray<FString>& ShuffledArray);

	void OpenDoor(ARiddleNPC* RiddleActor);

	UFUNCTION()
	void EndDialog(APawnInteractiveClass* SpokenActor);

};
