// Fill out your copyright notice in the Description page of Project Settings.


#include "PortalKillerLogic.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../../Character/CharacterPawnQuad.h"
#include "../../Elements/GeneralElements/Doors/Door.h"
#include "../Portal/Portal.h"	
#include "../Room/RoomKiller.h"

// Sets default values
APortalKillerLogic::APortalKillerLogic()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void APortalKillerLogic::BeginPlay(){

	Super::BeginPlay();

	PortalClass = StartPortal->GetClass();
	PortalStartPos = StartPortal->GetActorLocation();

	RoomKiller->EndArena.AddDynamic(this, &APortalKillerLogic::OpenDoor);
	
}

void APortalKillerLogic::OpenDoor() {
	
	Door->bOpenDoor = true;

	FTransform Transform;
	Transform.SetLocation(RoomKiller->PortalSpawnPosition->GetComponentLocation());
	Transform.SetRotation(FRotator::ZeroRotator.Quaternion());

	EndPortal = GetWorld()->SpawnActorDeferred<APortal>(PortalClass, Transform);
    EndPortal->NewPosition = PortalStartPos;
	EndPortal->FinishSpawning(Transform);

}


