// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "Components/BoxComponent.h"

// Sets default values
ADoor::ADoor(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	
	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Collider->SetupAttachment(RootComponent);

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetupAttachment(Collider);

	DoorMesh->SetWorldScale3D(FVector(0.65,0.65,0.65));
	Collider->SetWorldScale3D(FVector(4.25,0.25,5.5));

	bOpenDoor = false;
	bClose = false;
	Speed = 0.4f;
	Distance = 300.f;
	ID = 0;
}

// Called when the game starts or when spawned
void ADoor::BeginPlay(){
	
	Super::BeginPlay();

	FVector ActorPosition = GetActorLocation();

	SetDoorDirection(bClose);
	
}

// Called every frame
void ADoor::Tick(float DeltaTime){
	
	Super::Tick(DeltaTime);
	
	if(bOpenDoor){
		FVector ActorPosition = GetActorLocation();
		FVector NewLocation = FMath::Lerp(ActorPosition,FinalPosition, DeltaTime * Speed);
		SetActorLocation(NewLocation);
	}

}

void ADoor::SetDoorDirection(bool bIsClosed) {
	
	if(bIsClosed)
		FinalPosition = FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z - Distance);
	else
		FinalPosition = FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + Distance);

}


