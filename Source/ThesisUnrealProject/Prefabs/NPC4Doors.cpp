// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC4Doors.h"
#include "../Elements/GeneralElements/Door.h"
#include "../Character/CharacterPawnQuad.h"
#include "../Character/AllyAI/PawnInteractiveClass.h"
#include "Components/BoxComponent.h"
#include "../GameModeTutorial.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ANPC4Doors::ANPC4Doors()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	
	Doors = CreateDefaultSubobject<USceneComponent>(TEXT("Doors"));
	Doors->SetupAttachment(RootComponent);

	Door1 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Door1"));
	Door1->SetupAttachment(Doors);
	Door1->SetWorldScale3D(FVector(1.2f,1.2f,1.f));

	Door2 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Door2"));
	Door2->SetupAttachment(Doors);
	Door2->SetWorldScale3D(FVector(1.2f,1.2f,1.f));

	Door3 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Door3"));
	Door3->SetupAttachment(Doors);
	Door3->SetWorldScale3D(FVector(1.2f,1.2f,1.f));

	Door4 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Door4"));
	Door4->SetupAttachment(Doors);
	Door4->SetWorldScale3D(FVector(1.2f,1.2f,1.f));

	NPCs = CreateDefaultSubobject<USceneComponent>(TEXT("NPCs"));
	NPCs->SetupAttachment(RootComponent);

	NPC1 = CreateDefaultSubobject<UChildActorComponent>(TEXT("NPC1"));
	NPC1->SetupAttachment(NPCs);
	
}

// Called when the game starts or when spawned
void ANPC4Doors::BeginPlay()
{
	Super::BeginPlay();

	APawnInteractiveClass* NPCDoors = Cast<APawnInteractiveClass>(NPC1->GetChildActor());

	NPCDoors->LeftChoice.AddDynamic(this,&ANPC4Doors::LeftChoiceEvent);
	NPCDoors->RightChoice.AddDynamic(this,&ANPC4Doors::RightChoiceEvent);

}

// Called every frame
void ANPC4Doors::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANPC4Doors::LeftChoiceEvent() {
	Cast<ADoor>(Door1->GetChildActor())->bOpenDoor = true;
	Cast<ADoor>(Door2->GetChildActor())->bOpenDoor = true;	
	
	//Update Bartle's values
	AGameModeAbstract* GameMode = Cast<AGameModeAbstract>(GetWorld()->GetAuthGameMode());
	GameMode->Update->EquallyDistributedUpdate(Type::Achiever,Type::Killer);
	
	APawnInteractiveClass* NPC = Cast<APawnInteractiveClass>(NPC1->GetChildActor());
	NPC->SpeechContator += 1;
	NPC->Speak();
	NPC->SpeechContator += 1;
}

void ANPC4Doors::RightChoiceEvent() {
	Cast<ADoor>(Door3->GetChildActor())->bOpenDoor = true;
	Cast<ADoor>(Door4->GetChildActor())->bOpenDoor = true;

	//Update Bartle's values
	AGameModeAbstract* GameMode = Cast<AGameModeAbstract>(GetWorld()->GetAuthGameMode());
	GameMode->Update->EquallyDistributedUpdate(Type::Killer,Type::Achiever);
	
	APawnInteractiveClass* NPC = Cast<APawnInteractiveClass>(NPC1->GetChildActor());
	NPC->SpeechContator += 2;
	NPC->Speak();
}