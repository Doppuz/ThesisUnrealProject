// Fill out your copyright notice in the Description page of Project Settings.


#include "RumbleArenaDoorNpc.h"
#include "../../../Character/AllyAI/PawnInteractiveClass.h"
#include "../../GeneralElements/Door.h"

void ARumbleArenaDoorNpc::Tick(float DeltaTime) {
    
    if(bStart){
        Super::Tick(DeltaTime);
    }

}

void ARumbleArenaDoorNpc::BeginPlay() {
    
    Super::BeginPlay();

    FVector Pos = RewardSpawnPosition->GetComponentLocation();
    FRotator Rot = RewardSpawnPosition->GetComponentRotation();

    InteractiveActor = GetWorld()->SpawnActor<APawnInteractiveClass>(NpcClass,Pos,Rot);

    InteractiveActor->LeftChoice.AddDynamic(this,&ARumbleArenaDoorNpc::Start);

}

//Set bStart to true to begin the Arena.
void ARumbleArenaDoorNpc::Start() {
    
    RoomDoor->Speed = 3.f;

    InteractiveActor->Destroy();
    RoomDoor->bOpenDoor = true;
    bStart = true;

}

void ARumbleArenaDoorNpc::OpenDoor() {
    
    Super::OpenDoor();

    if(RoomDoor != nullptr){  
	    RoomDoor->SetDoorDirection(false);
    }else
        UE_LOG(LogTemp,Warning,TEXT("No door selected! (RumbleArenaWithDoor)"));

}
