// Fill out your copyright notice in the Description page of Project Settings.


#include "RumbleArenaDoorNpc.h"
#include "../../Character/AllyAI/PawnInteractiveClass.h"

void ARumbleArenaDoorNpc::Tick(float DeltaTime) {
    
    if(bStart){
        Super::Tick(DeltaTime);
    }

}

void ARumbleArenaDoorNpc::BeginPlay() {
    
    Super::BeginPlay();

    FVector Pos = RewardSpawnPosition->GetComponentLocation();
    FRotator Rot = RewardSpawnPosition->GetComponentRotation();

    APawnInteractiveClass* InteractiveActor = GetWorld()->SpawnActor<APawnInteractiveClass>(NpcClass,Pos,Rot);

    InteractiveActor->LeftChoice.AddDynamic(this,&ARumbleArenaDoorNpc::Start);

}

//Set bStart to true to begin the Arena.
void ARumbleArenaDoorNpc::Start() {
    
    bStart = true;

}
