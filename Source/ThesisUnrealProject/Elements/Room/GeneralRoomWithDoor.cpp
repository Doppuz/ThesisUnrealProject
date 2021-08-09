// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneralRoomWithDoor.h"
#include "Components/BoxComponent.h"
#include "../GeneralElements/Door.h"

AGeneralRoomWithDoor::AGeneralRoomWithDoor() {

    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	
	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Collider->SetupAttachment(RootComponent);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collider);

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
