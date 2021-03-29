// Fill out your copyright notice in the Description page of Project Settings.


#include "Graph.h"

Graph::Graph(){
}

Graph::~Graph(){
	TArray<Node*> Nodes;
	Map.GenerateKeyArray(Nodes);
	for (Node* N : Nodes) {
		for (Side* S : Map[N]){
			delete S;
		}
		delete N;
	}
}

//It now check only the adress. Need to check to not enter equals Node. AAAA Search this in future!!!!
void Graph::AddNode(Node* N) {
	if (!Map.Contains(N)) {
		TArray<Side*> List;
		Map.Add(N, List);
	}else
		UE_LOG(LogTemp, Warning, TEXT("Node already present in the list"));
}

void Graph::AddSide(Node* Begin, Node* End, float Weight) {
	Side* NewSide = new Side(Begin,End,Weight);
	Side* NewSideParent = new Side(End, Begin, Weight);
	if (!Map[Begin].Contains(NewSide))
		Map[Begin].Add(NewSide);
	if (!Map[End].Contains(NewSideParent))
		Map[End].Add(NewSideParent);
}

TArray<Node*> Graph::GetNodes(){
	TArray<Node*> Nodes;
	Map.GenerateKeyArray(Nodes);
	return Nodes;
}

TArray<Side*> Graph::GetSides(Node * N){
	if (!Map.Contains(N))
		return TArray<Side*>();
	else
		return Map[N];
}


