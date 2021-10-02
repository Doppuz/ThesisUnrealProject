// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeCell2.h"
#include "DrawDebugHelpers.h"

// Sets default values
AMazeCell2::AMazeCell2(){
 	
	 // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;

	bIsVisited = false;
	bIsRoom = false;
	RoomNumber = -1;

}

//Line trace between two nodes, if there is a wall, I destroy it.
void AMazeCell2::DestroyWall(AMazeCell2* Other) {
	
	LineTracing(Other->GetActorLocation());

}

void AMazeCell2::DestroyFloor() {
	
	LineTracing(-this->GetActorUpVector() * 2000);

}

void AMazeCell2::LineTracing(FVector Vector) {
	
	FHitResult Hit;
	FVector EndPosition = Vector;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	GetWorld()->LineTraceSingleByChannel(Hit,GetActorLocation(),EndPosition,ECollisionChannel::ECC_GameTraceChannel10,CollisionParams);

	if(Hit.GetActor() != nullptr){
		
		if(Hit.GetComponent()->IsA(UInstancedStaticMeshComponent::StaticClass())){

			Cast<UInstancedStaticMeshComponent>(Hit.GetComponent())->RemoveInstance(Hit.Item);
		
		}

	}

}
