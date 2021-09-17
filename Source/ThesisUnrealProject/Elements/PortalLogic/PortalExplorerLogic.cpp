// Fill out your copyright notice in the Description page of Project Settings.


#include "PortalExplorerLogic.h"
#include "Components/BoxComponent.h"
#include "../../GameManager/MazeCell2.h"
#include "../../GameManager/MazeManager.h"
#include "../Puzzle/PuzzleButton.h"
#include "../Maze/Maze.h"
#include "Kismet/GameplayStatics.h"
#include "../../Character/CharacterPawnQuad.h"
#include "Components/SpotLightComponent.h"
#include "../../Elements/Triggers/TriggerSpawnNight.h"
#include "../../Elements/GeneralElements/Doors/Door.h"
#include "../../Elements/Stairs/Stair.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "../../GameManager/MazeCell2.h"
#include "../Portal/Portal.h"	
#include "Engine/LevelStreaming.h"


APortalExplorerLogic::APortalExplorerLogic() {

	PrimaryActorTick.bCanEverTick = false;

}

void APortalExplorerLogic::BeginPlay() {

    Super::BeginPlay();

    TArray<AMazeCell2*> MazeCellMax = MazeManager->MaxPath;// = MazeManager->PopulateActor->MaxPath;

    FVector Pos = MazeCellMax[MazeCellMax.Num() - 1]->GetActorLocation() + FVector(0.f,0.f,-35.f);
    FRotator Rot = MazeCellMax[MazeCellMax.Num() - 1]->GetActorRotation();

	Button->SetActorLocation(Pos);
    Button->Overlap.AddDynamic(this,&APortalExplorerLogic::OpenDoorPuzzle);

	PortalClass = StartPortal->GetClass();
	PortalStartPos = StartPortal->GetActorLocation();

    StartPortal->Collider->OnComponentBeginOverlap.AddDynamic(this,&APortalExplorerLogic::OnOverlapPortal);
    
}

void APortalExplorerLogic::OpenDoorPuzzle(APuzzleButton* Elem) {
    
    if(Door != nullptr){
        Door->bOpenDoor = true;
    }else
        UE_LOG(LogTemp,Warning,TEXT("No door selected! (GeneralRoomWithDoor)"));

    ACharacterPawnQuad* MyPawn = Cast<ACharacterPawnQuad>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
	FLatentActionInfo LatentInfo;

    MyPawn->SpotLight->Intensity = 0.f;	
	UGameplayStatics::LoadStreamLevel(this, TEXT("Day"), true, true, LatentInfo);

    EndPortal = GetWorld()->SpawnActor<APortal>(PortalClass, MazeManager->MaxPath[MazeManager->MaxPath.Num() - 2]->GetActorLocation() - FVector(0.f,0.f,50.f), FRotator::ZeroRotator);
    EndPortal->NewPosition = PortalStartPos + FVector(0.f,0.f,100.f);

}

void APortalExplorerLogic::OnOverlapPortal(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit) {

	if(OtherActor->IsA(APawn::StaticClass()) && Cast<APawn>(OtherActor)->GetController()->IsA(APlayerController::StaticClass())){
        
        FLatentActionInfo LatentInfo;
        ACharacterPawnQuad* MyPawn = Cast<ACharacterPawnQuad>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));

        UGameplayStatics::UnloadStreamLevel(this, TEXT("Day"), LatentInfo, true);
		MyPawn->SpotLight->Intensity = 100000.f;
		MyPawn->SpotLight->AttenuationRadius = 3500.f;

    }
    
}
