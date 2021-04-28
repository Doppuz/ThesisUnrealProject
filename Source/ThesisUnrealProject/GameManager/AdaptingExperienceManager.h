// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

enum Type {Achiever, Killer, Socializer, Explorer};

/**
 * 
 */
class THESISUNREALPROJECT_API AdaptingExperienceManager
{
public:
	AdaptingExperienceManager(float* Achiever, float* Killer, float* Socializer, float* Explorer);
	~AdaptingExperienceManager();

	void WeightUpdate(Type,float, TArray<Type>);
	void EquallyDistributedUpdate(Type,float,TArray<Type>);

private:
	TMap<Type,float*> Types;
};
