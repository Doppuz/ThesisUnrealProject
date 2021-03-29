// Fill out your copyright notice in the Description page of Project Settings.


#include "Space.h"

Space::Space(float X, float Y, float SizeX, float SizeY){
	this->X = X;
	this->Y = Y;
	this->SizeX = SizeX;
	this->SizeY = SizeY;
	this->Size = SizeX * SizeY;
}

Space::~Space(){
}
