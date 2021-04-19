// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeCell.h"
#include "CoupleStruct.h"

// Sets default values
AMazeCell::AMazeCell(){

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	MeshPlaneComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane Mesh"));
	MeshPlaneComponent->SetupAttachment(RootComponent);

	MeshWall1Component = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall1 Mesh"));
	MeshWall1Component->SetupAttachment(RootComponent);

	MeshWall2Component = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall2 Mesh"));
	MeshWall2Component->SetupAttachment(RootComponent);

	MeshWall3Component = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall3 Mesh"));
	MeshWall3Component->SetupAttachment(RootComponent);

	MeshWall4Component = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall4 Mesh"));
	MeshWall4Component->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AMazeCell::BeginPlay(){
	Super::BeginPlay();
	
}

void AMazeCell::HideObstacleWall() {
	MeshPlaneComponent->SetStaticMesh(nullptr);
	MeshWall1Component->SetStaticMesh(nullptr);
	MeshWall2Component->SetStaticMesh(nullptr);
	MeshWall3Component->SetStaticMesh(nullptr);
	MeshWall4Component->SetStaticMesh(nullptr);
}

void AMazeCell::HideWall(int WallNumber) {
	LastHiddenWall = WallNumber;
	switch(WallNumber){
		case 1:
			MeshWall1Component->SetStaticMesh(nullptr);
			WallNumbers -= 1;
			break;
		case 2:
			MeshWall2Component->SetStaticMesh(nullptr);
			WallNumbers -= 1;
			break;
		case 3:
			MeshWall3Component->SetStaticMesh(nullptr);
			WallNumbers -= 1;
			break;
		case 4:
			MeshWall4Component->SetStaticMesh(nullptr);
			WallNumbers -= 1;
			break;
		default:
			UE_LOG(LogTemp,Warning,TEXT("Not valid wall number"));
			LastHiddenWall = -1;
			break;
	}

}

//Return true if a wall is hidden, false otherwise.
bool AMazeCell::HideWallBool(int WallNumber, Coord& OppositeCell, int& WallToDelete){
	switch (WallNumber) {
	case 1:
		if (MeshWall1Component->GetStaticMesh() == nullptr || I == 0 || bIsObstacle)
			return false;
		MeshWall1Component->SetStaticMesh(nullptr);
		OppositeCell.CoordI = I - 1;
		OppositeCell.CoordJ = J;
		WallToDelete = 3;
		break;
	case 2:
		if (MeshWall2Component->GetStaticMesh() == nullptr || J == 9 || bIsObstacle)
			return false;
		MeshWall2Component->SetStaticMesh(nullptr);
		OppositeCell.CoordI = I;
		OppositeCell.CoordJ = J + 1;
		WallToDelete = 4;
		break;
	case 3:
		if (MeshWall3Component->GetStaticMesh() == nullptr || I == 9 || bIsObstacle)
			return false;
		MeshWall3Component->SetStaticMesh(nullptr);
		OppositeCell.CoordI = I + 1;
		OppositeCell.CoordJ = J;
		WallToDelete = 1;
		break;
	case 4:
		if (MeshWall4Component->GetStaticMesh() == nullptr || J == 0 || bIsObstacle)
			return false;
		MeshWall4Component->SetStaticMesh(nullptr);
		OppositeCell.CoordI = I;
		OppositeCell.CoordJ = J - 1;
		WallToDelete = 2;
		break;
	default:
		UE_LOG(LogTemp, Warning, TEXT("Not valid wall number"));
		break;
	}
	return true;
}