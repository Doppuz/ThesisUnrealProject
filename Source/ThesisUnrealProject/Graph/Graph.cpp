// Fill out your copyright notice in the Description page of Project Settings.


#include "Graph.h"

Graph::Graph(){
}

Graph::~Graph(){
}

//It now check only the adress. Need to check to not enter equals Node. AAAA Search this in future!!!!
void Graph::AddNode(Node* N) {
	if (!Map.Contains(N)) {
		TArray<Side*> List;
		Map.Add(N, List);
	}else
		UE_LOG(LogTemp, Warning, TEXT("Node already present in the list"));
}

void Graph::AddSide(Side* S) {
	if (!Map.Contains(S->From))
		Map.Add(S->From);
	if (!Map.Contains(S->To))
		Map.Add(S->To);
	if (!Map[S->From].Contains(S))
		Map[S->From].Add(S);
}

//Valuto se utile.
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


