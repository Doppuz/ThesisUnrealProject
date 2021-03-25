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
	~Graph();

	TMap<Node*, TArray<Side*>> Map;
	TArray<Node*> Leaves;

	void AddNode(Node*);

	void AddSide(Side*);

	TArray<Node*> GetNodes();
	TArray<Side*> GetSides(Node* N);

};
