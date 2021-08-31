// Fill out your copyright notice in the Description page of Project Settings.


#include "RiddleAndDoor.h"
#include "../../../Character/AllyAI/RiddleNPC.h"
#include "../../../Elements/GeneralElements/Door.h"

// Sets default values
ARiddleAndDoor::ARiddleAndDoor(){

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	RiddleNpcPos = CreateDefaultSubobject<USceneComponent>(TEXT("RiddleNpcPos"));
	RiddleNpcPos->SetupAttachment(RootComponent);

	DoorPos = CreateDefaultSubobject<USceneComponent>(TEXT("DoorPos"));
	DoorPos->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ARiddleAndDoor::BeginPlay(){

	Super::BeginPlay();

	GetWorld()->SpawnActor<ADoor>(DoorClass,DoorPos->GetComponentLocation(), FRotator::ZeroRotator);
	GetWorld()->SpawnActor<ARiddleNPC>(RiddleNpcClass,RiddleNpcPos->GetComponentLocation(), FRotator::ZeroRotator);

}