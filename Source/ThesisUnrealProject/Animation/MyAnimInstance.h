// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class THESISUNREALPROJECT_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UMyAnimInstance();

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Generic")
	float Speed;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Generic")
	float Angle;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Generic")
	FRotator AngleArmRotation;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

};
