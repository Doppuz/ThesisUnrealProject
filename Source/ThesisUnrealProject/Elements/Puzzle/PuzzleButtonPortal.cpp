// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleButtonPortal.h"
#include "Kismet/GameplayStatics.h"
#include "../../Character/CharacterPawnQuad.h"
#include "Components/SpotLightComponent.h"
#include "../../Elements/GeneralElements/Doors/Door.h"
#include "../Portal/Portal.h"	
#include "Engine/LevelStreaming.h"


void APuzzleButtonPortal::BeginPlay() {
    
    Super::BeginPlay();

    PortalStartPos = StartPortal->GetActorLocation();

    Overlap.AddDynamic(this,&APuzzleButtonPortal::OpenDoorPuzzle);

}

void APuzzleButtonPortal::OpenDoorPuzzle(APuzzleButton* Elem) {
    
    if(Door != nullptr){
        Door->bOpenDoor = true;
    }else
        UE_LOG(LogTemp,Warning,TEXT("No door selected! (GeneralRoomWithDoor)"));

    ACharacterPawnQuad* MyPawn = Cast<ACharacterPawnQuad>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
	FLatentActionInfo LatentInfo;

    MyPawn->SpotLight->Intensity = 0.f;	
	UGameplayStatics::LoadStreamLevel(this, TEXT("Day"), true, true, LatentInfo);

    APortal* EndPortal = GetWorld()->SpawnActor<APortal>(PortalClass, EndSpawnPosition, FRotator::ZeroRotator);
    EndPortal->NewPosition = PortalStartPos + FVector(0.f,0.f,100.f);

}