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
	
	FHitResult Hit;
	FVector EndPosition = Other->GetActorLocation();
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);
	CollisionParams.AddIgnoredActor(Other);

	GetWorld()->LineTraceSingleByChannel(Hit,GetActorLocation(),EndPosition,ECollisionChannel::ECC_GameTraceChannel10,CollisionParams);

	if(Hit.GetActor() != nullptr){
		
		if(Hit.GetComponent()->IsA(UInstancedStaticMeshComponent::StaticClass())){

			Cast<UInstancedStaticMeshComponent>(Hit.GetComponent())->RemoveInstance(Hit.Item);
		
		}

	}

}

void AMazeCell2::DestroyFloor() {
	
	FHitResult Hit;
	FVector EndPosition = -this->GetActorUpVector() * 2000;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	GetWorld()->LineTraceSingleByChannel(Hit,GetActorLocation(),EndPosition,ECollisionChannel::ECC_GameTraceChannel10,CollisionParams);

	if(Hit.GetActor() != nullptr){
		
		if(Hit.GetComponent()->IsA(UInstancedStaticMeshComponent::StaticClass())){

			Cast<UInstancedStaticMeshComponent>(Hit.GetComponent())->RemoveInstance(Hit.Item);
		
		}

	}

}

// Called when the game starts or when spawned
void AMazeCell2::BeginPlay()
{
	Super::BeginPlay();
	
}
