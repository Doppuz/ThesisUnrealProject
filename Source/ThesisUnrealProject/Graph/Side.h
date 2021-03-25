// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Node.h"
#include "CoreMinimal.h"

class THESISUNREALPROJECT_API Side{
public:
	Side(Node* From,Node* To, float Weight);
	~Side();

	Node* From;
	Node* To;
	float Weight;
};
