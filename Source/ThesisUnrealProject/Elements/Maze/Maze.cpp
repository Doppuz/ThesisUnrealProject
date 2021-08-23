// Fill out your copyright notice in the Description page of Project Settings.


#include "Maze.h"

// Sets default values
AMaze::AMaze(){
	
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;

	FloorInstances = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("FloorInstances"));
    FloorInstances->SetupAttachment(RootComponent);

	WallInstances = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("WallInstances"));
    WallInstances->SetupAttachment(RootComponent);
	WallInstances->SetRelativeLocation(FVector(-50.f,-450.f,280.f));

	MeshLenght = 1000.f;

}

void AMaze::CreateCell(FTransform Transform) {

	FloorInstances->AddInstance(Transform);

	FVector FloorVector = Transform.GetLocation();
	FVector Vector = FloorVector - FVector(MeshLenght/2, 0.f,0.f);
	FRotator Rotator(0.f,90.f,0.f);
	Transform.SetLocation(Vector);

	WallInstances->AddInstance(Transform);

	Vector = FloorVector - FVector(0.f, MeshLenght/2,0.f);
	Rotator = FRotator(0.f,90.f,0.f);
	Transform.SetLocation(Vector);
	Transform.SetRotation(Rotator.Quaternion());

	WallInstances->AddInstance(Transform);
	
}

void AMaze::CreateLast2Walls(FTransform Transform) {

	FVector FloorVector = Transform.GetLocation();
	FVector Vector = FloorVector - FVector(MeshLenght/2, 0.f,0.f);
	FRotator Rotator(0.f,90.f,0.f);
	Transform.SetLocation(Vector);

	WallInstances->AddInstance(Transform);

	Vector = FloorVector - FVector(0.f, MeshLenght/2,0.f);
	Rotator = FRotator(0.f,90.f,0.f);
	Transform.SetLocation(Vector);
	Transform.SetRotation(Rotator.Quaternion());

	WallInstances->AddInstance(Transform);

}

// Called when the game starts or when spawned
void AMaze::BeginPlay(){

	Super::BeginPlay();
	
}