// Fill out your copyright notice in the Description page of Project Settings.


#include "SpacePartitionMazeGenerator.h"
#include "DrawDebugHelpers.h"
#include "../Graph/Graph.h"
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
	Graph p;
	Space p1(1,2,3,4);
	Space p2(1, 2, 3, 4);
	p.AddNode(&p1);
	p.AddNode(&p2);
	Side S(&p1, &p2, 22);
	p.AddSide(&S);
	UE_LOG(LogTemp,Warning,TEXT("%i"),p.Map.Num());
	UE_LOG(LogTemp, Warning, TEXT("%i"), p.Map[&p1].Num());
}

// Called every frame
void ASpacePartitionMazeGenerator::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
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

