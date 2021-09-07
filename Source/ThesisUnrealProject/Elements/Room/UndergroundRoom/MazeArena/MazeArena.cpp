// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeArena.h"
#include "Components/BoxComponent.h"
#include "../../../../GameManager/MazeCell2.h"
#include "../../../../GameManager/MazeManager.h"
#include "../../../../GameManager/MazePopulate.h"
#include "../../../Puzzle/PuzzleButton.h"
#include "../../../Maze/Maze.h"
#include "Kismet/GameplayStatics.h"
#include "../../../../Character/CharacterPawnQuad.h"
#include "Components/SpotLightComponent.h"
#include "../../../../Elements/Triggers/TriggerSpawnNight.h"
#include "../../../../Elements/GeneralElements/Door.h"
#include "../../../../Elements/Stairs/Stair.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "../../../../GameManager/MazeCell2.h"
#include "../../../Portal/Portal.h"

void AMazeArena::BeginPlay() {

    Super::BeginPlay();

    TArray<AMazeCell2*> MazeCellMax = MazeManager->MaxPath;// = MazeManager->PopulateActor->MaxPath;

    FVector Pos = MazeCellMax[MazeCellMax.Num() - 1]->GetActorLocation() + FVector(0.f,0.f,-35.f);
    FRotator Rot = MazeCellMax[MazeCellMax.Num() - 1]->GetActorRotation();

    Button = GetWorld()->SpawnActor<APuzzleButton>(PuzzleButtonClass, Pos, Rot);
    Button->Overlap.AddDynamic(this,&AMazeArena::OpenDoor);

    FAttachmentTransformRules TransformRules(EAttachmentRule::KeepWorld,true);
    Button->AttachToActor(MazeManager->MazeActor,TransformRules);

    
}

void AMazeArena::OpenDoor() {
    
    Super::OpenDoor();

    ACharacterPawnQuad* MyPawn = Cast<ACharacterPawnQuad>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
	FLatentActionInfo LatentInfo;

    MyPawn->SpotLight->Intensity = 0.f;	
	UGameplayStatics::LoadStreamLevel(this, TEXT("Day"), true, true, LatentInfo);

    StartPortal->Collider->OnComponentBeginOverlap.AddDynamic(this,&AMazeArena::OnOverlapPortal);

}

void AMazeArena::OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit) {
    
    if(OtherActor->IsA(ACharacterPawnQuad::StaticClass())){
		ACharacterPawnQuad* MyPawn = Cast<ACharacterPawnQuad>(OtherActor);
		
		if(MyPawn->GetController()->IsA(APlayerController::StaticClass())){

            for(ATriggerSpawnNight* Trigger: Triggers)
                Trigger->Destroy();

		}
	}

}

void AMazeArena::OnOverlapPortal(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit) {

	if(OtherActor->IsA(APawn::StaticClass()) && Cast<APawn>(OtherActor)->GetController()->IsA(APlayerController::StaticClass())){
        
        TArray<ULevelStreaming *> Livelli = GetWorld()->GetStreamingLevels();
        int a = 0;

    }
    
}