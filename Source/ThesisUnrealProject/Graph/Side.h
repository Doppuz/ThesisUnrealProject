// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Node.h"
#include "CoreMinimal.h"

class AMazeCell;

template<class F>
class THESISUNREALPROJECT_API Side{
public:
	Side(F* From,F* To, float Weight);
	~Side();

	F* From;
	F* To;
	float Weight;
};

//Implementation below

template<class F>
Side<F>::Side(F* From, F* To, float Weight){
	this->From = From;
	this->To = To;
	this->Weight = Weight;
}


template<class F>
Side<F>::~Side()
{
}