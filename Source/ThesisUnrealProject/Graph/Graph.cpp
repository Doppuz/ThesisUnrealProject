// Fill out your copyright notice in the Description page of Project Settings.


#include "Graph.h"



/*template<typename F,typename S>
Graph<F,S>::~Graph(){
	TArray<F*> Nodes;
	Map.GenerateKeyArray(Nodes);
	for (F* N : Nodes) {
		for (S* Edg : Map[N]){
			delete Edg;
		}
		delete N;
	}
}*/

//It now check only the adress. Need to check to not enter equals Node. AAAA Search this in future!!!!
//template<typename F,typename S>
void Graph::AddNode(Space* N) {
	if (!Map.Contains(N)) {
		TArray<Side*> List;
		Map.Add(N, List);
	}else
		UE_LOG(LogTemp, Warning, TEXT("Node already present in the list"));
}

//template<typename F,typename S>
void Graph::AddSide(Space* Begin, Space* End, float Weight) {
	Side* NewSide = new Side(Begin,End,Weight);
	Side* NewSideParent = new Side(End, Begin, Weight);
	if (!Map[Begin].Contains(NewSide))
		Map[Begin].Add(NewSide);
	if (!Map[End].Contains(NewSideParent))
		Map[End].Add(NewSideParent);
}

//template<typename F,typename S>
TArray<Space*> Graph::GetNodes(){
	TArray<Space*> Nodes;
	Map.GenerateKeyArray(Nodes);
	return Nodes;
}

//template<typename F,typename S>
TArray<Side*> Graph::GetSides(Space * N){
	if (!Map.Contains(N))
		return TArray<Side*>();
	else
		return Map[N];
}

//template<class F, class S>
void Graph::DeleteNode(Space* Spc) {
	Map.Remove(Spc);
}


//template<typename F,typename S>
TArray<Space*> Graph::GetLeaves(float RoomLimit) {
	TArray<Space*> Leaves = GetNodes();
	TArray<Space*> Result;

	if(Leaves.Num() > 1)
		Leaves.RemoveAt(0);

	for (Space* TmpSpace: Leaves) {

		if (Map[TmpSpace].Num() < 2 && TmpSpace->Size > RoomLimit)
			Result.Add(TmpSpace);
		
	}
	return Result;
}

//template<typename F,typename S>
TArray<Space*> Graph::GetLeavesNoSpace() {
	TArray<Space*> Leaves = GetNodes();
	TArray<Space*> Result;

	if(Leaves.Num() > 1)
		Leaves.RemoveAt(0);

	for (Space* TmpSpace: Leaves) {

		if (Map[TmpSpace].Num() < 2)
			Result.Add(TmpSpace);
		
	}
	return Result;
}

//template<class F, class S>
TArray<Space*> Graph::GetNodesMaxDistance() {
	TArray<Space*> Leaves;
	int MaxDepth = 0;
	for(Space* S: GetNodes()){
		int Depth = GetDepth(S);
		if(Depth > MaxDepth){
			MaxDepth = Depth;
			Leaves.Empty();
			Leaves.Add(S);
		}else if(Depth == MaxDepth && MaxDepth != 0)
			Leaves.Add(S);
	}
	TArray<Space*> Fathers;
	for(Space* Spc: Leaves){
		if(!Fathers.Contains(Map[Spc][0]->To))
			Fathers.Add(Map[Spc][0]->To);
	}
	return Fathers;	
}

//template<typename F,typename S>
int Graph::GetDepth(Space* Spc) {
	if(Map[Spc].Num() == 2)
		return 0;
	else
		return 1 + GetDepth(Map[Spc][0]->To);	
}


