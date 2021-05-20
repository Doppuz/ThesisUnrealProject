// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnInteractiveClass.generated.h"

USTRUCT(BlueprintType)
struct FQuestion{
	GENERATED_BODY()

    UPROPERTY(EditAnywhere,BlueprintReadWrite)
    FString Question;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
    TArray<FString> Answers;

};

UCLASS()
class THESISUNREALPROJECT_API APawnInteractiveClass : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APawnInteractiveClass();

//-----Speech-----

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Speak)
	TArray<FString> Speech;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = Speak)
	int SpeechContator;

//-----Questions-----
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Speak)
	TArray<FQuestion> Questions;

	//Actually right now it doesn't do anything.
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = Speak)
	int AnswerContator;
	
	//it determines the position of the question. If it is -1, the question has already been done.
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Speak)
	int QuestionAt;

	//Ally ID
	UPROPERTY(EditAnywhere)
	int ID;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual void Speak();
	virtual void Ask();
	virtual void Choice(int Answer);
	virtual void StartInteraction();
	virtual void EndInteraction();

};
