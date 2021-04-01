// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Space.h"
#include "Node.h"
#include "CoreMinimal.h"

//template<typename F>
class THESISUNREALPROJECT_API Side{
public:
	Side(Space* From,Space* To, float Weight);
	~Side();

	Space* From;
	Space* To;
	float Weight;
};
