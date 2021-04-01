#pragma once

#include "CoreMinimal.h"
#include "Node.h"
#include "../SPTMaze/Cell.h"


class THESISUNREALPROJECT_API Space : public Node {
public:
	Space(float X, float Y, float SizeX, float SizeY);
	~Space();

	float X;
	float Y;
	float SizeX;
	float SizeY;
	float Size;

	ACell* Room = nullptr;
};
