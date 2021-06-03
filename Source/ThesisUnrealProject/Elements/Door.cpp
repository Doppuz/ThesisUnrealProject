// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "Components/BoxComponent.h"
#include "PuzzleButton.h"

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
	Distance = 200.f;
	ID = 0;
}

// Called when the game starts or when spawned
void ADoor::BeginPlay(){
	
	Super::BeginPlay();

	FVector ActorPosition = GetActorLocation();

	if(bClose)
		FinalPosition = FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z - Distance);
	else
		FinalPosition = FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + Distance);
	
}

// Called every frame
void ADoor::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
	
	CheckActorOverlap();
	
	if(bOpenDoor){
		FVector ActorPosition = GetActorLocation();
		FVector NewLocation = FMath::Lerp(ActorPosition,FinalPosition, DeltaTime * Speed);
		SetActorLocation(NewLocation);
	}
}

//It works only for buttons.
void ADoor::CheckActorOverlap() {
	
	//In this case the condition is not used.
	if(Activator.Num() == 0)
		return;

	for(int i = 0; i < Activator.Num(); i++){
		APuzzleButton* Button = Cast<APuzzleButton>(Activator[i]);
		if(!Button->bDisableOverlap)
			return;
	}		

	bOpenDoor = true;
}
