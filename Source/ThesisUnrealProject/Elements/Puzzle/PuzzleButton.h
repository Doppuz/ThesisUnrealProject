// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSelectedDelegate,APuzzleButton*,Elem);

UCLASS()
class THESISUNREALPROJECT_API APuzzleButton : public AActor
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	APuzzleButton();

	static int IDCounter;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	class UBoxComponent* Collider;

	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	UBoxComponent* Trigger;

	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = "true"), Category = Materials)
	UMaterial* ButtonColor;

	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit);

	int GetID();

	bool bDisableOverlap;

	//Used mainly in the prefabs to open the door. (ForthPuzzle.cpp)
	bool bIsPressed;

	//Called when pressed
	FSelectedDelegate Overlap;

	UPROPERTY(VisibleAnywhere)
	int ID;

};
