// Fill out your copyright notice in the Description page of Project Settings.


#include "RumbleArenaDoor.h"
#include "../Elements/GeneralElements/Doors/Door.h"
#include "../Elements/GeneralElements/CoinController.h"
#include "../Tutorial/RumbleArena.h"
#include "NPC1Door2.h"

// Sets default values
ARumbleArenaDoor::ARumbleArenaDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	
	Doors = CreateDefaultSubobject<USceneComponent>(TEXT("Doors"));
	Doors->SetupAttachment(RootComponent);

	Door1 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Door1"));
	Door1->SetupAttachment(Doors);
	Door1->SetWorldScale3D(FVector(1.2f,1.2f,1.f));

	RumbleArenas = CreateDefaultSubobject<USceneComponent>(TEXT("RumbleArenas"));
	RumbleArenas->SetupAttachment(RootComponent);

	RumbleArena1 = CreateDefaultSubobject<UChildActorComponent>(TEXT("RumbleArena1"));
	RumbleArena1->SetupAttachment(RumbleArenas);
	
	PreChoices = CreateDefaultSubobject<USceneComponent>(TEXT("PreChoices"));
	PreChoices->SetupAttachment(RootComponent);

	PreChoice1 = CreateDefaultSubobject<UChildActorComponent>(TEXT("PreChoice1"));
	PreChoice1->SetupAttachment(PreChoices);

}

// Called when the game starts or when spawned
void ARumbleArenaDoor::BeginPlay()
{
	Super::BeginPlay();

	ARumbleArena* RumbleArena01 = Cast<ARumbleArena>(Cast<UChildActorComponent>(RumbleArena1)->GetChildActor());
	RumbleArena01->EndArena.AddDynamic(this,&ARumbleArenaDoor::EndEvent);

	//Needed to set the turn number to 1.
	ANPC1Door2* NPCDoor2 = Cast<ANPC1Door2>(PreChoice1->GetChildActor());
	APawnInteractiveClass* NPC = Cast<APawnInteractiveClass>(NPCDoor2->NPC1->GetChildActor());
	NPC->LeftChoice.AddDynamic(this,&ARumbleArenaDoor::LeftChoice);

}

void ARumbleArenaDoor::EndEvent() {
	ADoor* Door = Cast<ADoor>(Door1->GetChildActor());
	Door->bOpenDoor = true;

	ARumbleArena* RumbleArena01 =Cast<ARumbleArena>(RumbleArena1->GetChildActor());
	
	ANPC1Door2* PreChoice01 = Cast<ANPC1Door2>(PreChoice1->GetChildActor());;

	if(RumbleArena01->RewardClass != nullptr && PreChoice01->bLeftChoice){
			ACoinController* Coin = GetWorld()->SpawnActor<ACoinController>(RumbleArena01->RewardClass,RumbleArena01->RewardSpawnPosition->GetComponentLocation(),
				RumbleArena01->RewardSpawnPosition->GetComponentRotation());
			Coin->SetActorScale3D(FVector(0.4f,0.4f,0.4f));
	}
}

void ARumbleArenaDoor::LeftChoice() {

	ARumbleArena* RumbleArena01 = Cast<ARumbleArena>(RumbleArena1->GetChildActor());
	RumbleArena01->TurnNumbers = 0;

}