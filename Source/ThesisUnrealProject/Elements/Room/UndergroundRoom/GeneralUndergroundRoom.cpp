// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneralUndergroundRoom.h"
#include "../../../GameManager/MazeManager.h"
#include "../../../GameManager/MazeCell2.h"
#include "../../Maze/Maze.h"
#include "../../../Elements/GeneralElements/Door.h"
#include "../../../Elements/Stairs/Stair.h"
#include "../../Portal/Portal.h"


AGeneralUndergroundRoom::AGeneralUndergroundRoom() {

    SpawnPortalPosition = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPortalPosition"));
    SpawnPortalPosition->SetupAttachment(RootComponent);
    
}

void AGeneralUndergroundRoom::BeginPlay() {
    
    Super::BeginPlay();

    FTransform SpawnLocAndRotation;
    MazeManager = GetWorld()->SpawnActorDeferred<AMazeManager>(MazeManagerClass, SpawnLocAndRotation);
    MazeManager->Depth = -750.f;
    MazeManager->Length = 5;
    MazeManager->Height = 5;
    MazeManager->MazeRooms = 0;
    MazeManager->PopulateMaze = false;
    MazeManager->FinishSpawning(SpawnLocAndRotation);

    MazeManager->MazeActor->SetActorLocation(PortalPosition);

    StartPortal = GetWorld()->SpawnActor<APortal>(PortalClass, SpawnPortalPosition->GetComponentLocation(), SpawnPortalPosition->GetComponentRotation());
    StartPortal->SetActorScale3D(FVector(2.5f,2.5f,1.f));
    StartPortal->NewPosition = MazeManager->MazeGraph->GetNodes()[0]->GetActorLocation();

    EndPortal = GetWorld()->SpawnActor<APortal>(PortalClass, MazeManager->MaxPath[MazeManager->MaxPath.Num() - 1]->GetActorLocation(), FRotator::ZeroRotator);
    EndPortal->NewPosition = StartPortal->GetActorLocation();

}