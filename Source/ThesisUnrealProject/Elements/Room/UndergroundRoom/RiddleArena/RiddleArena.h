// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../GeneralUndergroundRoom.h"
#include "RiddleArena.generated.h"

class ADoor;
class ARiddleNPC;
class APawnInteractiveClass;

UCLASS()
class THESISUNREALPROJECT_API ARiddleArena : public AGeneralUndergroundRoom
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, Category = "Elements")
	TSubclassOf<ADoor> DoorClass;

	UPROPERTY(EditAnywhere, Category = "Elements")
	TSubclassOf<ARiddleNPC> RiddleNpcClass;
	
	UPROPERTY(EditAnywhere, Category = "Elements")
	TSubclassOf<APawnInteractiveClass> SpokenNpcClass;

	void GenerateRiddleDoors();

	UFUNCTION()
	void OpenRiddleDoor(ARiddleNPC* RiddleActor);

	UFUNCTION()
	void EndDialog(APawnInteractiveClass* SpokenActor);

	//Pointers to the maze manager class.
	TArray<TArray<FString>>* Speech;
	TArray<TArray<FString>>* Questions;
	TArray<TArray<FString>>* OldSpeech;
	TArray<TArray<FString>>* OldQuestions;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void LoadFromFile(TArray<TArray<FString>>&, FString FileName);

	int ShuffleArray(TArray<FString>& ShuffledArray);

};