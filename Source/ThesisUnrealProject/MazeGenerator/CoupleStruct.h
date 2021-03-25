// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

struct Coord{
	int CoordI;
	int CoordJ;

	Coord(int I, int J) : CoordI{ I }, CoordJ{ J } {}

	Coord() {}
};
