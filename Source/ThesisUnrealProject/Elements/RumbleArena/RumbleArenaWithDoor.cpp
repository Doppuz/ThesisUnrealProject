// Fill out your copyright notice in the Description page of Project Settings.


#include "RumbleArenaWithDoor.h"
#include "../GeneralElements/Door.h"

void ARumbleArenaWithDoor::BeginPlay() {

    Super::BeginPlay();

    EndArena.AddDynamic(this,&ARumbleArenaWithDoor::OpenDoor);
}

void ARumbleArenaWithDoor::OpenDoor() {
    
    if(Door != nullptr){
        Door->bOpenDoor = true;
    }else
        UE_LOG(LogTemp,Warning,TEXT("No door selected! (RumbleArenaWithDoor)"));

}


