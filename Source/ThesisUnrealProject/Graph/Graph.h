// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Side.h"
#include "Node.h"
#include "CoreMinimal.h"

/**
 * 
 */
class THESISUNREALPROJECT_API Graph{

public:
	Graph();
	virtual ~Graph();

	void AddNode(Node*);

	void AddSide(Node*, Node*, float);

	TArray<Node*> GetNodes();
	TArray<Side*> GetSides(Node* N);

protected:

	TMap<Node*, TArray<Side*>> Map;
};
