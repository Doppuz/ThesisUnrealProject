// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneralRoomWithDoor.h"
#include "Components/BoxComponent.h"
#include "../GeneralElements/Doors/Door.h"

AGeneralRoomWithDoor::AGeneralRoomWithDoor() {	
    
    PrimaryActorTick.bCanEverTick = false;

    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	
	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Collider->SetupAttachment(RootComponent);
    Collider->SetWorldScale3D(FVector(35.50f,35.50f,0.50f));
    Collider->SetWorldLocation(FVector(0.f,0.f,4.8f));

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collider);
    Mesh->SetWorldScale3D(FVector(0.65f,0.65f,0.65f));

}


void AGeneralRoomWithDoor::BeginPlay() {

    Super::BeginPlay();

}

void AGeneralRoomWithDoor::OpenDoor() {
    
    if(Door != nullptr){
        Door->bOpenDoor = true;
    }else
        UE_LOG(LogTemp,Warning,TEXT("No door selected! (GeneralRoomWithDoor)"));

}
