// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeCell.h"
#include "CoupleStruct.h"
#include "Components/BoxComponent.h"
#include "../Elements/CrateElements.h"

// Sets default values
AMazeCell::AMazeCell(){

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = SceneComponent;

	Meshes = CreateDefaultSubobject<USceneComponent>(TEXT("Meshes"));
	Meshes->SetupAttachment(RootComponent);

	SpawnPoints = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPoints"));
	SpawnPoints->SetupAttachment(RootComponent);

	BoxTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	BoxTrigger->SetupAttachment(Meshes);

	MeshPlaneComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane Mesh"));
	MeshPlaneComponent->SetupAttachment(Meshes);

	MeshWall1Component = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall1 Mesh"));
	MeshWall1Component->SetupAttachment(Meshes);

	MeshWall2Component = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall2 Mesh"));
	MeshWall2Component->SetupAttachment(Meshes);

	MeshWall3Component = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall3 Mesh"));
	MeshWall3Component->SetupAttachment(Meshes);

	MeshWall4Component = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall4 Mesh"));
	MeshWall4Component->SetupAttachment(Meshes);

	SpawnPointWall1 = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPoint1 Mesh"));
	SpawnPointWall1->SetupAttachment(SpawnPoints);

	SpawnPointWall2 = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPoint2 Mesh"));
	SpawnPointWall2->SetupAttachment(SpawnPoints);

	SpawnPointWall3 = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPoint3 Mesh"));
	SpawnPointWall3->SetupAttachment(SpawnPoints);

	SpawnPointWall4 = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPoint4 Mesh"));
	SpawnPointWall4->SetupAttachment(SpawnPoints);

}

// Called when the game starts or when spawned
void AMazeCell::BeginPlay(){
	Super::BeginPlay();
	Walls.Add(1);
	Walls.Add(2);
	Walls.Add(3);
	Walls.Add(4);
}

void AMazeCell::HideObstacleWall() {
	MeshPlaneComponent->SetStaticMesh(nullptr);
	MeshWall1Component->SetStaticMesh(nullptr);
	MeshWall2Component->SetStaticMesh(nullptr);
	MeshWall3Component->SetStaticMesh(nullptr);
	MeshWall4Component->SetStaticMesh(nullptr);

	Walls.Empty();
}

void AMazeCell::HideWall(int WallNumber) {
	LastHiddenWall = WallNumber;
	switch(WallNumber){
		case 1:
			MeshWall1Component->SetStaticMesh(nullptr);
			Walls.Remove(1);
			WallNumbers -= 1;
			break;
		case 2:
			MeshWall2Component->SetStaticMesh(nullptr);
			Walls.Remove(2);
			WallNumbers -= 1;
			break;
		case 3:
			MeshWall3Component->SetStaticMesh(nullptr);
			Walls.Remove(3);
			WallNumbers -= 1;
			break;
		case 4:
			MeshWall4Component->SetStaticMesh(nullptr);
			Walls.Remove(4);
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

void AMazeCell::AddElem(AActor* Actor) {
	ObjectsInside.Add(Actor);
}

void AMazeCell::RemoveElem(AActor* Actor) {
	ObjectsInside.Remove(Actor);
	Actor->Destroy();
}

void AMazeCell::RemoveAllElem() {
	for(int i=0; i < ObjectsInside.Num(); i++){
		ObjectsInside[i]->Destroy();
	}
}

//Method for spawning the CrateElems in front of a wall.
void AMazeCell::PopulateElem(TSubclassOf<ACrateElements> ElemClass) {
	
	int NumExtr = FMath::RandRange(0,Walls.Num() - 1);
	
	if(Walls.Num() == 0)
		return;

	FVector Position;
	FRotator Rotation;
	AActor* Actor;

	switch (Walls[NumExtr]){
	case 1:
		//Position = GetActorLocation() + FVector( MeshWall1Component->GetRelativeLocation().X + 50,0,-333); //+ MeshWall1Component->GetRelativeLocation();
		Position = SpawnPointWall1->GetComponentLocation();
		Rotation = FRotator(0,90,0);
		Actor = GetWorld()->SpawnActor<ACrateElements>(ElemClass,Position,Rotation);
		AddElem(Actor);
		break;
	case 2:
		//Position = GetActorLocation() + FVector(0, MeshWall2Component->GetRelativeLocation().Y + 50,-333); // + MeshWall2Component->GetRelativeLocation();
		Position = SpawnPointWall2->GetComponentLocation();
		Rotation = FRotator(0,180,0);
		Actor = GetWorld()->SpawnActor<ACrateElements>(ElemClass,Position,Rotation);
		AddElem(Actor);
		break;
	case 3:
		//Position = GetActorLocation() + FVector( MeshWall3Component->GetRelativeLocation().X - 200,0,-333);// + MeshWall3Component->GetRelativeLocation();
		Position = SpawnPointWall3->GetComponentLocation();
		Rotation = FRotator(0,-90,0);
		Actor = GetWorld()->SpawnActor<ACrateElements>(ElemClass,Position,Rotation);
		AddElem(Actor);
		break;
	case 4:
		//Position = GetActorLocation()  + FVector(0, MeshWall4Component->GetRelativeLocation().Y - 200,-333); // + MeshWall4Component->GetRelativeLocation();
		Position = SpawnPointWall4->GetComponentLocation();
		Rotation = FRotator(0,0,0);
		Actor = GetWorld()->SpawnActor<ACrateElements>(ElemClass,Position,Rotation);
		AddElem(Actor);
		break;
	
	default:
		break;
	}
}