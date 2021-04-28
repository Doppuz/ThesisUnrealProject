// Fill out your copyright notice in the Description page of Project Settings.


#include "Side.h"
#include "Node.h"
#include "../GameManager/MazeCell.h"

//template<typename F>
Side::Side(AMazeCell* From, AMazeCell* To, float Weight){
	this->From = From;
	this->To = To;
	this->Weight = Weight;
}


//template<typename F>
Side::~Side()
{
}
