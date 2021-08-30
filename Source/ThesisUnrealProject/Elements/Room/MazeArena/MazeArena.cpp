// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeArena.h"
#include "Components/BoxComponent.h"
#include "../../../GameManager/MazeCell2.h"
#include "../../../GameManager/MazeManager.h"
#include "../../../GameManager/MazePopulate.h"
#include "../../Puzzle/PuzzleButton.h"
#include "../../Maze/Maze.h"
#include "Kismet/GameplayStatics.h"
#include "../../../Character/CharacterPawnQuad.h"
#include "Components/SpotLightComponent.h"
#include "../../../Elements/Triggers/TriggerSpawnNight.h"
#include "../../../Elements/GeneralElements/Door.h"
#include "Components/BoxComponent.h"

AMazeArena::AMazeArena() {
    
    Collider->SetCollisionProfileName("NoCollision");

}


void AMazeArena::BeginPlay() {

    Super::BeginPlay();

    const FTransform SpawnLocAndRotation;
    MazeManager = GetWorld()->SpawnActorDeferred<AMazeManager>(MazeManagerClass, SpawnLocAndRotation);
    MazeManager->Depth = -750.f;
    MazeManager->Length = 5;
    MazeManager->Height = 5;
    MazeManager->MazeRooms = 0;
    MazeManager->PopulateMaze = false;
    MazeManager->FinishSpawning(SpawnLocAndRotation);

    MazeManager->MazeActor->WallInstances->RemoveInstance(0);

    TArray<AMazeCell2*> MazeCellMax = MazeManager->MaxPath;// = MazeManager->PopulateActor->MaxPath;

    FVector Pos = MazeCellMax[MazeCellMax.Num() - 1]->GetActorLocation() + FVector(0.f,0.f,-35.f);
    FRotator Rot = MazeCellMax[MazeCellMax.Num() - 1]->GetActorRotation();

    APuzzleButton* Button = GetWorld()->SpawnActor<APuzzleButton>(PuzzleButtonClass, Pos, Rot);
    Button->Overlap.AddDynamic(this,&AMazeArena::OpenDoor);

    FAttachmentTransformRules TransformRules(EAttachmentRule::KeepWorld,true);
    Button->AttachToActor(MazeManager->MazeActor,TransformRules);
    
}


void AMazeArena::SetMazeLocation(FVector Pos) {
    
    MazeManager->MazeActor->SetActorLocation(Pos);

}

FVector AMazeArena::GetMazeLocation() {
    
    return MazeManager->MazeActor->GetActorLocation();

}

FVector AMazeArena::GetMazeInstanceLocation(int Index) {

    FTransform Pos;
    MazeManager->MazeActor->FloorInstances->GetInstanceTransform(Index,Pos,true);
    return Pos.GetLocation();

}

void AMazeArena::SetMazeRotation(FRotator Rot){

    MazeManager->MazeActor->SetActorRotation(Rot);

}

void AMazeArena::OpenDoor() {
    
    Super::OpenDoor();

    ACharacterPawnQuad* MyPawn = Cast<ACharacterPawnQuad>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
	FLatentActionInfo LatentInfo;

    MyPawn->SpotLight->Intensity = 0.f;	
	UGameplayStatics::LoadStreamLevel(this, TEXT("Day"), true, true, LatentInfo);

    RoomDoor->SetDoorDirection(false);

}

void AMazeArena::CreateNightTrigger(FTransform Transform) {

    ATriggerSpawnNight* Trigger = GetWorld()->SpawnActorDeferred<ATriggerSpawnNight>(TriggerNightClass,Transform);
    Trigger->SetActorScale3D(FVector(15.f,1.2f,1.f));
    Trigger->AttenuationRadius = 2500.f;
    Trigger->FinishSpawning(Transform);
    Trigger->Trigger->OnComponentBeginOverlap.AddDynamic(this,&AMazeArena::OnOverlap);

    Triggers.Add(Trigger);
    
}


void AMazeArena::OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit) {
    
    if(OtherActor->IsA(ACharacterPawnQuad::StaticClass())){
		ACharacterPawnQuad* MyPawn = Cast<ACharacterPawnQuad>(OtherActor);
		
		if(MyPawn->GetController()->IsA(APlayerController::StaticClass())){

            RoomDoor->bOpenDoor = true;
            for(ATriggerSpawnNight* Trigger: Triggers)
                Trigger->Destroy();

		}
	}

}