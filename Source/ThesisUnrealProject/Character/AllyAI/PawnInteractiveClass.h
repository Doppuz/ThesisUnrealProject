// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnInteractiveClass.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLeftDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRightDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEndDialogDelegate,APawnInteractiveClass*, SpokenActor);

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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this pawn's properties
	APawnInteractiveClass();

	static int IDCount;

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

#pragma region Components

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = General)
	class UBoxComponent* Collider;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = General)
	UStaticMeshComponent* Mesh;

#pragma endregion

#pragma region Equipment

	void Equipment();

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Equipment)
	UStaticMesh* MeshToEquip;

#pragma endregion

#pragma region Speech

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Speak)
	TArray<FString> Speech;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = Speak)
	int SpeechContator;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = Speak)
	bool bAlreadySpoken;

#pragma endregion

#pragma region Question

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

	FLeftDelegate LeftChoice;
	FRightDelegate RightChoice;
	FEndDialogDelegate EndDialog;

#pragma endregion

#pragma region Focus

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Focus)
	bool bFocus;

#pragma endregion
};
