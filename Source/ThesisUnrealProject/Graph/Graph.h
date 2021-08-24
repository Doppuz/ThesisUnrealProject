// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameManager/MazeCell.h"
#include "Side.h"
#include "Node.h"
#include "CoreMinimal.h"

template<class F>
class THESISUNREALPROJECT_API Graph{

public:

	void AddNode(F*);

	void AddSide(F*, F*, float);

	TArray<F*> GetNodes();
	TArray<Side<F>*> GetSides(F* N);

	void DeleteNode(F*);
	void DeleteSide(F*,F*);

	TArray<F*> GetLeaves(float RoomLimit);
	TArray<F*> GetLeavesNoSpace();
	TArray<F*> GetNodesMaxDistance();

	F* GetCurrentNode();

	void SetCurrentNode(F*);

	void SetVisitedToZero();

	//Move the current node to the next cell.
	void MoveCurrentNode(F* );

	int GetGraphSize();

protected:

	TMap<F*, TArray<Side<F>*>> Map;

private:
	int GetDepth(F*);

	//Used to store the current node the player is in right now.
	F* CurrentNode = nullptr;
};

// Implementation down below

template<class F>
void Graph<F>::AddNode(F* N) {
	if (!Map.Contains(N)) {
		TArray<Side<F>*> List;
		Map.Add(N, List);
	}else
		UE_LOG(LogTemp, Warning, TEXT("Node already present in the list"));
}

template<class F>
void Graph<F>::AddSide(F* Begin, F* End, float Weight) {
	Side<F>* NewSide = new Side<F>(Begin,End,Weight);
	Side<F>* NewSideParent = new Side<F>(End, Begin, Weight);
	if (!Map[Begin].Contains(NewSide))
		Map[Begin].Add(NewSide);
	if (!Map[End].Contains(NewSideParent))
		Map[End].Add(NewSideParent);
}


template<class F>
TArray<F*> Graph<F>::GetNodes(){
	TArray<F*> Nodes;
	Map.GenerateKeyArray(Nodes);
	return Nodes;
}


template<class F>
TArray<Side<F>*> Graph<F>::GetSides(F * N){
	if (!Map.Contains(N))
		return TArray<Side<F>*>();
	else
		return Map[N];
}


template<class F>
void Graph<F>::DeleteNode(F* Spc) {
	Map.Remove(Spc);
}

template<class F>
void Graph<F>::DeleteSide(F* First,F* Second) {

	//Remove the side from First to Second	
	for(Side<F>* S : GetSides(First)){

		if(S->To == Second){
			Map[First].Remove(S);
			break;
		}

	}

	//Remove the side from Second to First
	for(Side<F>* S : GetSides(Second)){

		if(S->To == First){
			Map[Second].Remove(S);
			break;
		}

	}

}


template<class F>
TArray<F*> Graph<F>::GetLeaves(float RoomLimit) {
	TArray<F*> Leaves = GetNodes();
	TArray<F*> Result;

	if(Leaves.Num() > 1)
		Leaves.RemoveAt(0);

	for (F* TmpSpace: Leaves) {

		//if (Map[TmpSpace].Num() < 2 && TmpSpace->Size > RoomLimit)
		//	Result.Add(TmpSpace);
		
	}
	return Result;
}


template<class F>
TArray<F*> Graph<F>::GetLeavesNoSpace() {
	TArray<F*> Leaves = GetNodes();
	TArray<F*> Result;

	if(Leaves.Num() > 1)
		Leaves.RemoveAt(0);

	for (F* TmpSpace: Leaves) {

		if (Map[TmpSpace].Num() < 2)
			Result.Add(TmpSpace);
		
	}
	return Result;
}


template<class F>
TArray<F*> Graph<F>::GetNodesMaxDistance() {
	TArray<F*> Leaves;
	int MaxDepth = 0;
	for(F* S: GetNodes()){
		int Depth = GetDepth(S);
		if(Depth > MaxDepth){
			MaxDepth = Depth;
			Leaves.Empty();
			Leaves.Add(S);
		}else if(Depth == MaxDepth && MaxDepth != 0)
			Leaves.Add(S);
	}
	TArray<F*> Fathers;
	for(F* Spc: Leaves){
		if(!Fathers.Contains(Map[Spc][0]->To))
			Fathers.Add(Map[Spc][0]->To);
	}
	return Fathers;	
}


template<class F>
F* Graph<F>::GetCurrentNode() {
	return CurrentNode;
}

template<class F>
void Graph<F>::SetCurrentNode(F* CurNode) {
	
	CurrentNode = CurNode;

}

template<class F>
void Graph<F>::SetVisitedToZero() {
	for(F* Cell: GetNodes())
    	Cell->bIsVisited = false;
}


template<class F>
void Graph<F>::MoveCurrentNode(F* NewNode) {
	if(CurrentNode == nullptr)
		CurrentNode = NewNode;
	else{
		TArray<Side<F> *> Sides = GetSides(CurrentNode);
		for(Side<F>* S: Sides){
			if(S->To == NewNode){
				CurrentNode = NewNode;
				break;
			}	
		}
		if(CurrentNode != NewNode){
			UE_LOG(LogTemp,Warning,TEXT("Error, %s doesn't cointain %s as adjacent node"),
				*CurrentNode->GetName(), *NewNode->GetName());
			//Needed for not updating the UI.
			NewNode->bIsVisited = true;
		}
	}
}


template<class F>
int Graph<F>::GetGraphSize() {
	return Map.Num();	
}


template<class F>
int Graph<F>::GetDepth(F* Spc) {
	if(Map[Spc].Num() == 2)
		return 0;
	else
		return 1 + GetDepth(Map[Spc][0]->To);	
}

