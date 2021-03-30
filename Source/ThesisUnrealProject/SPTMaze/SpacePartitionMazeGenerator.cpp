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
	Space* RootSpace = new Space(0,0, 25000, 25000);
	Maze.AddNode(RootSpace);
	TArray<Node*> b = Maze.GetNodes();
	Space* tmp = (Space*) b[0];
	DrawSquare(0, 0, 25000, 25000);
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
	
	//Space creation
	int i = 0;
	int Direction = 0;
	do{
		int NumExtr = FMath::RandRange(0, Leaves.Num() - 1);
		Space* Father = (Space*) Leaves[NumExtr];
		
		float NewLine;
		float NewFatherPos;
		int Limit = 6000;

		switch (Direction){	
		case 0: {
			float LeftPos = Father->X - (Father->SizeX) / 2;
			float RightPos = Father->X + (Father->SizeX) / 2;
			int I = 0;
			do {
				NewLine = FMath::RandRange(-(Father->SizeX) / 2, (Father->SizeX) / 2);
				NewFatherPos = Father->X + NewLine;
				if(I > 20){
					Limit -= 500;
					I = 0;
				}
				I += 1;	
			} while (NewFatherPos - LeftPos < Limit || RightPos - NewFatherPos < Limit);

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
			int I = 0;
			do{
				NewLine = FMath::RandRange(-(Father->SizeY) / 2, (Father->SizeY) / 2);
				NewFatherPos = Father->Y + NewLine;
				if(I > 20){
					Limit -= 500;
					I = 0;
				}
				I += 1;
			} while (NewFatherPos - LeftPos < Limit || RightPos - NewFatherPos < Limit);

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

	//Room creation
	Leaves = Maze.GetLeavesNoSpace();
	CreateRooms(Leaves);
	
}

void ASpacePartitionMazeGenerator::CreateRooms(TArray<Node *> Leaves) {
	for(Node* N: Leaves){
		Space* TempSpace = (Space*) N;
		float XDist = FMath::RandRange(TempSpace->X - (TempSpace->SizeX)/2,TempSpace->X + (TempSpace->SizeX)/2);
		float YDist = FMath::RandRange(TempSpace->Y - (TempSpace->SizeY)/2,TempSpace->Y + (TempSpace->SizeY)/2);
		float XStartPos = FMath::RandRange(0,2) ? TempSpace->X  - XDist : TempSpace->X  + XDist;
		float YStartPos = FMath::RandRange(0,2) ? TempSpace->Y  - YDist : TempSpace->Y  + YDist;


		/*int XCellNumber = (TempSpace->SizeX + XDist) / CellSize;
		int YCellNumber = (TempSpace->SizeY + YDist) / CellSize;*/
		
		float XScale = FMath::RandRange(7.f,(TempSpace->SizeX - 2000) / CellSize);
		float YScale = FMath::RandRange(7.f,(TempSpace->SizeY - 2000) / CellSize);
		

		FVector Origin(TempSpace->X,TempSpace->Y,0);
		FRotator Rotation(0,0,0);
		FVector Scale(XScale,YScale,0);
		ACell* Cell = GetWorld()->SpawnActor<ACell>(CellClass,Origin,Rotation);
		Cell->SetActorScale3D(Scale);
		/*for(int i = 0; i < CellNumber; i++){
			for(int i = 0; i < CellNumber; i++){
				FVector Origin(i*(CellSize),);
				FRotator Rotation(0,0,0);
				AMazeCell* CellActor = GetWorld()->SpawnActor<AMazeCell>(CellClass,Origin,Rotation);
			}
		}*/
	}
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

