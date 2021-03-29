// Fill out your copyright notice in the Description page of Project Settings.


#include "SpacePartitionMazeGenerator.h"
#include "DrawDebugHelpers.h"
#include "../Graph/GraphSpaces.h"
#include "../Graph/Space.h"

// Sets default values
ASpacePartitionMazeGenerator::ASpacePartitionMazeGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpacePartitionMazeGenerator::BeginPlay(){
	Super::BeginPlay();
	Space* RootSpace = new Space(0,0, 50000, 50000);
	Maze.AddNode(RootSpace);
	TArray<Node*> b = Maze.GetNodes();
	Space* tmp = (Space*) b[0];
	DrawSquare(0, 0, 50000, 50000);
	CreateMaze();
}

// Called every frame
void ASpacePartitionMazeGenerator::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
	//DrawLine(FVector(0,-25000,0), FVector(0, +25000, 0));
	//DrawLine(FVector(-25000, 0, 0), FVector(25000, 0, 0));
	//DrawSquare(0, 0, 50000, 50000);
}

void  ASpacePartitionMazeGenerator::CreateMaze() {
	TArray<Node*> Leaves = Maze.GetLeaves(RoomSizeLimit);
	int i = 0;
	int Direction = 0;
	do{
		int NumExtr = FMath::RandRange(0, Leaves.Num() - 1);
		Space* Father = (Space*) Leaves[NumExtr];
		
		float NewLine;
		float NewFatherPos;

		switch (Direction){	
		case 0: {
			float LeftPos = Father->X - (Father->SizeX) / 2;
			float RightPos = Father->X + (Father->SizeX) / 2;
			do {
				NewLine = FMath::RandRange(-(Father->SizeX) / 2, (Father->SizeX) / 2);
				NewFatherPos = Father->X + NewLine;
			} while (NewFatherPos - LeftPos < 5000 || RightPos - NewFatherPos < 5000);

			Space* LeftRoom = new Space(LeftPos + (NewFatherPos - LeftPos) / 2, Father->Y, NewFatherPos - LeftPos, Father->SizeY);
			Space* RightRoom = new Space(NewFatherPos + (RightPos - NewFatherPos) / 2, Father->Y, RightPos - NewFatherPos, Father->SizeY);

			Maze.AddNode(LeftRoom);
			Maze.AddNode(RightRoom);

			Maze.AddSide(Father, LeftRoom, 0);
			Maze.AddSide(Father, RightRoom, 0);

			DrawSquare(LeftRoom->X, LeftRoom->Y, LeftRoom->SizeX, LeftRoom->SizeY);
			DrawDebugPoint(GetWorld(), FVector(LeftRoom->X, LeftRoom->Y, 0), 10, FColor(0, 255, 0), true);
			DrawDebugPoint(GetWorld(), FVector(RightRoom->X, RightRoom->Y, 0), 10, FColor(0, 255, 0), true);
			break;
		}
		case 1: {

			float LeftPos = Father->Y - (Father->SizeY) / 2;
			float RightPos = Father->Y + (Father->SizeY) / 2;
			do{
				NewLine = FMath::RandRange(-(Father->SizeY) / 2, (Father->SizeY) / 2);
				NewFatherPos = Father->Y + NewLine;
			} while (NewFatherPos - LeftPos < 5000 || RightPos - NewFatherPos < 5000);

			Space* LeftRoom = new Space(Father->X, LeftPos + (NewFatherPos - LeftPos) / 2, Father->SizeX, NewFatherPos - LeftPos);
			Space* RightRoom = new Space(Father->X, NewFatherPos + (RightPos - NewFatherPos) / 2, Father->SizeX, RightPos - NewFatherPos);

			Maze.AddNode(LeftRoom);
			Maze.AddNode(RightRoom);

			Maze.AddSide(Father, LeftRoom, 0);
			Maze.AddSide(Father, RightRoom, 0);

			DrawSquare(LeftRoom->X, LeftRoom->Y, LeftRoom->SizeX, LeftRoom->SizeY);
			DrawDebugPoint(GetWorld(), FVector(LeftRoom->X, LeftRoom->Y, 0), 10, FColor(0, 255, 0), true);
			DrawDebugPoint(GetWorld(), FVector(RightRoom->X, RightRoom->Y, 0), 10, FColor(0, 255, 0), true);
			break;
		}
		default:
			UE_LOG(LogTemp, Warning, TEXT("Switch case Error"));
			break;
		}
		Leaves = Maze.GetLeaves(RoomSizeLimit);
		Direction = (Direction + 1) % 2;
	} while (Leaves.Num() != 0);
}

void ASpacePartitionMazeGenerator::DrawLine(FVector Start, FVector End) {
	DrawDebugLine(
		GetWorld(),
		Start,
		End,
		FColor(0, 0, 255),
		false,
		50.f,
		50,
		50.f
	);
}


void  ASpacePartitionMazeGenerator::DrawSquare(float X, float Y, float SizeX, float SizeY) {
	DrawLine(FVector(X - (SizeX / 2),Y - (SizeY / 2), 0), FVector(X - (SizeX / 2), Y + (SizeY / 2), 0));
	DrawLine(FVector(X + (SizeX / 2), Y - (SizeY / 2), 0), FVector(X + (SizeX / 2), Y + (SizeY / 2), 0));
	DrawLine(FVector(X - (SizeX / 2), Y - (SizeY / 2), 0), FVector(X + (SizeX / 2), Y - (SizeY / 2), 0));
	DrawLine(FVector(X - (SizeX / 2), Y + (SizeY / 2), 0), FVector(X + (SizeX / 2), Y + (SizeY / 2), 0));
}

