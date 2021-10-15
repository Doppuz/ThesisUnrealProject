// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "Components/BoxComponent.h"

int ADoor::IDCount = 0; 

// Sets default values
ADoor::ADoor(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetupAttachment(RootComponent);
	DoorMesh->SetWorldLocation(FVector(0.f,0.f,-60.f));
	DoorMesh->SetWorldRotation(FRotator(0.f,-90.f,0.f));
	DoorMesh->SetWorldScale3D(FVector(1.25f,1.25f,1.f));

	SubDoorRightMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SubDoorRightMesh"));
	SubDoorRightMesh->SetupAttachment(DoorMesh);
	SubDoorRightMesh->SetWorldLocation(FVector(-10.f,130.f,0.f));
	
	SubDoorLeftMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SubDoorLeftMesh"));
	SubDoorLeftMesh->SetupAttachment(DoorMesh);
	SubDoorLeftMesh->SetWorldLocation(FVector(-10.f,-130.f,0.f));

	bOpenDoor = false;
	bClose = false;
	Speed = 1.f;
	Distance = 300.f;
	ID = 0;
	LeftRotation = FRotator(0.f,90.f,0.f);
	RightRotation = FRotator(0.f,-90.f,0.f);

}

// Called when the game starts or when spawned
void ADoor::BeginPlay(){
	
	Super::BeginPlay();

	FVector ActorPosition = GetActorLocation();

	SetDoorDirection(bClose);

	ID = IDCount;
	IDCount = (IDCount + 1) % 50000;

	Rot1 = SubDoorLeftMesh->GetComponentRotation();
	Rot2 = SubDoorRightMesh->GetComponentRotation();
	
}

// Called every frame
void ADoor::Tick(float DeltaTime){
	
	Super::Tick(DeltaTime);
	
	if(bOpenDoor){
		//FVector ActorPosition = GetActorLocation();
		//FVector NewLocation = FMath::Lerp(ActorPosition,FinalPosition, DeltaTime * Speed);
		//SetActorLocation(NewLocation);

		FRotator LeftDoorRot = SubDoorLeftMesh->GetComponentRotation();
		FRotator NewRotation = FMath::Lerp(LeftDoorRot,Rot1 + LeftRotation, DeltaTime * Speed);
		SubDoorLeftMesh->SetWorldRotation(NewRotation);

		FRotator RightDoorRot = SubDoorRightMesh->GetComponentRotation();
		FRotator NewRotation2 = FMath::Lerp(RightDoorRot,Rot2 + RightRotation, DeltaTime * Speed);
		SubDoorRightMesh->SetWorldRotation(NewRotation2);

	}

}

void ADoor::SetDoorDirection(bool bIsClosed) {
	
	if(bIsClosed){
		LeftRotation = FRotator(0.f,-90.f,0.f);
		RightRotation = FRotator(0.f,90.f,0.f);
	}

}

void ADoor::OpenDoor() {
	
	bOpenDoor = true;

}


