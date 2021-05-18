// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "PawnInteractiveClass.h"

#include "PawnAllyNPC.generated.h"

class AGunController;
class ASquaredProjectile;


USTRUCT(BlueprintType)
struct FQuestion{
	GENERATED_BODY()

    UPROPERTY(EditAnywhere,BlueprintReadWrite)
    FString Question;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
    TArray<FString> Answers;

};

UCLASS()
class THESISUNREALPROJECT_API APawnAllyNPC : public APawnInteractiveClass{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APawnAllyNPC();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = Camera)
	USpringArmComponent* CameraArmComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = Camera)
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = General)
	class UBoxComponent* Collider;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = General)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = General)
	UStaticMeshComponent* EquipmentMesh;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = General)
	USceneComponent* ProjectileSpawnPosition;

	//Projectile class
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Projectile)
	TSubclassOf<ASquaredProjectile> ProjectileClass;
	
	//Time between 2 projectile
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Projectile)
	float ProjectileTimeout;

	//Healt
	UPROPERTY(EditDefaultsOnly)
	float MaxHealth;

	UPROPERTY(VisibleAnywhere)
	float Health;

	//LineTracing max range
	float MaxRange;

		//SpeakDialog 
	void Speak();
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Speak)
	TArray<FString> Speech;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = Speak)
	int SpeechContator;

	//QuestionsDialog
	void Ask();

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Speak)
	TArray<FQuestion> Questions;

	//Actually right now it doesn't do anything.
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = Speak)
	int AnswerContator;
	
	//it determines the position of the question. If it is -1, the question has already been done.
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Speak)
	int QuestionAt;

	//Ally ID
	UPROPERTY(VisibleAnywhere)
	int ID;

	//Methods for Questions Response.
	
//------ Equipment --------
	void Equipment();

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Equipment)
	UStaticMesh* MeshToEquip;

//---- General ---
	void Choice(int);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	//InteractiveActor
	APawnInteractiveClass* InteractiveActor;

	void StartInteraction() override;
	void EndInteraction() override;
};
