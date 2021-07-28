// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

enum Type {Achiever, Killer, Socializer, Explorer};

/**
 * 
 */
class THESISUNREALPROJECT_API AdaptiveExperience{

public:

	AdaptiveExperience();
	~AdaptiveExperience();

	TMap<Type,float> Types;
	
	TMap<Type,float> TypesQuestionary;

	void EquallyDistributedUpdate(Type IncreasedType,float IncreasedValue,Type DecreasedType,float DecreasedValue);

	void EquallyDistributedUpdate(Type IncreasedType, Type DecreasedType);

	void DistributedUpdate(Type IncreasedType, Type DecreasedType);

	TMap<Type,float> GetBartleTypes();

	void ResetValue();

	float IncreaseValue;

// --- Save ---

	void SaveFile(FString);
	void LoadFile(FString);

};
