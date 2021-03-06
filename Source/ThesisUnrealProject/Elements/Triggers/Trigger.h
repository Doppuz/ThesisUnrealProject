// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Trigger.generated.h"

UCLASS()
class THESISUNREALPROJECT_API ATrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrigger();

	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* Trigger;

	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit);

	//tick it if you want the trigger to hide your visibility.
	UPROPERTY(EditAnywhere, Category = "Visibility")
	bool bBlockVisibility;

	//Change the visibility based on the parameter.
	void ChangeVisibility(bool);



protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Define the overlap type (begin/end). It is called in the BeginPlay.
	virtual void TypeOfOverlap();

};
