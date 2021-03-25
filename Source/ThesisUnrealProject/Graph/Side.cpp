// Fill out your copyright notice in the Description page of Project Settings.


#include "Side.h"
#include "Node.h"

Side::Side(Node* From, Node* To, float Weight){
	this->From = From;
	this->To = To;
	this->Weight = Weight;
}

Side::~Side()
{
}
