// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BartleManagerGameInstance.generated.h"

enum Type {Achiever, Killer, Socializer, Explorer};

/**
 * 
 */
UCLASS()
class THESISUNREALPROJECT_API UBartleManagerGameInstance : public UGameInstance{
	GENERATED_BODY()
	
public:

	UBartleManagerGameInstance();

	// --- Bartle types ----
	
	TMap<Type,float> Types;
	
	TMap<Type,float> TypesQuestionary;

	void EquallyDistributedUpdate(Type IncreasedType,float IncreasedValue,Type DecreasedType,float DecreasedValue);

	void EquallyDistributedUpdate(Type IncreasedType, Type DecreasedType);

	void DistributedUpdate(Type IncreasedType, Type DecreasedType);

	TMap<Type,float> GetBartleTypes();

	void ResetValue();

	float IncreaseValue;

};
