// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeCell.h"

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
void AMazeCell::BeginPlay()
{
	Super::BeginPlay();
	
}


