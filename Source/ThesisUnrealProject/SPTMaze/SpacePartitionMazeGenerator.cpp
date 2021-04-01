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
	TArray<Space*> b = Maze.GetNodes();
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
	TArray<Space*> Leaves = Maze.GetLeaves(RoomSizeLimit);
	
	//Space creation
	int i = 0;
	int Direction = 0;
	do{
		int NumExtr = FMath::RandRange(0, Leaves.Num() - 1);
		Space* Father = Leaves[NumExtr];
		
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
	CreateCorridors();
	
}

void ASpacePartitionMazeGenerator::CreateRooms(TArray<Space *> Leaves) {
	for(Space* TempSpace: Leaves){
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
		TempSpace->Room = Cell;
	}
}

void ASpacePartitionMazeGenerator::CreateCorridors() {
	Graph GraphCopy = Maze;
	TArray<Space*> Leaves;
	Leaves = GraphCopy.GetNodesMaxDistance();
	do{
		int TotalNumber = Leaves.Num();
		for(int i = 0; i < TotalNumber; i++) {
			TArray<Side*> TmpSide = GraphCopy.GetSides(Leaves[0]);
			if(TmpSide.Num() == 3){
				//UE_LOG(LogTemp,Warning,TEXT("%x link %x"),TmpSide[1]->To,TmpSide[2]->To);
				GenerateCorridors(TmpSide[1]->To,TmpSide[2]->To);
				GraphCopy.DeleteNode(TmpSide[1]->To);
				GraphCopy.DeleteNode(TmpSide[2]->To);
			}else{
				//UE_LOG(LogTemp,Warning,TEXT("%x link %x"),TmpSide[0]->To,TmpSide[1]->To);
				GenerateCorridors(TmpSide[0]->To,TmpSide[1]->To);
				GraphCopy.DeleteNode(TmpSide[0]->To);
				GraphCopy.DeleteNode(TmpSide[1]->To);
			}
			Leaves.RemoveAt(0);
		}
		Leaves = GraphCopy.GetNodesMaxDistance();
	}while(Leaves.Num() != 0);
	int h = 1;
}

void ASpacePartitionMazeGenerator::GenerateCorridors(Space* Spc1,Space* Spc2) {
	FVector Point = FVector((Spc1->X + Spc2->X)/2,(Spc1->Y + Spc2->Y)/2,0);
	FRotator Rotation(0,0,0);
	UE_LOG(LogTemp,Warning,TEXT("%f link %f"),FMath::Square(Spc2->X - Spc1->X),FMath::Square(Spc2->Y - Spc1->Y));
	float XScale = 1,YScale = 1;
	if(FMath::Square(Spc2->X - Spc1->X) == 0){
		XScale = (FMath::Sqrt(FMath::Square(Point.X - Spc1->X)) * 2) / 500;
	}else{
		YScale = (FMath::Sqrt(FMath::Square(Point.Y - Spc1->Y)) * 2) / 500;
	}
	FVector Scale(XScale,YScale,0);
	UE_LOG(LogTemp,Warning,TEXT("%f bo %f"),(FMath::Sqrt(FMath::Square(Point.X - Spc1->X)) * 2) / 500, (FMath::Sqrt(FMath::Square(Point.Y - Spc1->Y)) * 2) / 500);
	ACell* Cell = GetWorld()->SpawnActor<ACell>(CellClass,Point,Rotation);
	Cell->SetActorScale3D(Scale);
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

