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
	FloorInstances->SetNotifyRigidBodyCollision(true);
	FloorInstances->ComponentTags.Add("ResetJump");

	WallInstances = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("WallInstances"));
    WallInstances->SetupAttachment(RootComponent);
	WallInstances->SetRelativeLocation(FVector(-50.f,-450.f,280.f));

	ObstacleInstances = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("ObstacleInstances"));
    ObstacleInstances->SetupAttachment(RootComponent);

	MetalCrateInstances = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("MetalCrateInstances"));
	MetalCrateInstances->SetupAttachment(RootComponent);

	MeshLenght = 768.f;
	ObstacleSize = 100.f;
	ObstacleHeight = 190.f;

}

void AMaze::CreateFloor(FTransform Transform) {

	FloorInstances->AddInstance(Transform);
	
}

void AMaze::CreateWalls(FTransform Transform) {

	CreateHorizontalWall(Transform);
	CreateVerticalWall(Transform);

}

void AMaze::CreateHorizontalWall(FTransform Transform) {
	
	FVector Vector = Transform.GetLocation() - FVector(0.f, MeshLenght/2 -0.f,0.f);
	FRotator Rotator = FRotator(0.f,90.f,0.f);
	Transform.SetLocation(Vector);
	Transform.SetRotation(Rotator.Quaternion());

	WallInstances->AddInstance(Transform);

}

void AMaze::CreateVerticalWall(FTransform Transform) {
	
	FVector Vector = Transform.GetLocation() - FVector(MeshLenght/2, -0.f,0.f);
	Transform.SetLocation(Vector);

	WallInstances->AddInstance(Transform);

}

void AMaze::CreateObstacle(FTransform Transform) {
	
	ObstacleInstances->AddInstance(Transform);

}

void AMaze::CreateMetalCrate(FTransform Transform) {
	
	MetalCrateInstances->AddInstance(Transform);

}


