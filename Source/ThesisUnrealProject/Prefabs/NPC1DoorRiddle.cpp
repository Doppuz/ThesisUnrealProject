// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC1DoorRiddle.h"
#include "../Elements/Door.h"
#include "../Character/PawnInteractiveClass.h"
#include "Components/BoxComponent.h"
#include "../Character/CharacterPawnQuad.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ANPC1DoorRiddle::ANPC1DoorRiddle()
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

	NPCs = CreateDefaultSubobject<USceneComponent>(TEXT("NPCs"));
	NPCs->SetupAttachment(RootComponent);

	NPC1 = CreateDefaultSubobject<UChildActorComponent>(TEXT("NPC1"));
	NPC1->SetupAttachment(NPCs);

}

// Called when the game starts or when spawned
void ANPC1DoorRiddle::BeginPlay()
{
	Super::BeginPlay();

	APawnInteractiveClass* NPC = Cast<APawnInteractiveClass>(Cast<UChildActorComponent>(NPC1)->GetChildActor());

	NPC->LeftChoice.AddDynamic(this,&ANPC1DoorRiddle::LeftChoiceEvent);
	NPC->RightChoice.AddDynamic(this,&ANPC1DoorRiddle::RightChoiceEvent);
	NPC->EndDialog.AddDynamic(this,&ANPC1DoorRiddle::EndChoiceEvent);

}

// Called every frame
void ANPC1DoorRiddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANPC1DoorRiddle::LeftChoiceEvent() {

	APawnInteractiveClass* NPC = Cast<APawnInteractiveClass>(Cast<UChildActorComponent>(NPC1)->GetChildActor());

	NPC->SpeechContator += 1;
	NPC->Speak();
	NPC->SpeechContator = NPC->Speech.Num() - 2;

	ADoor* Door = Cast<ADoor>(Cast<UChildActorComponent>(Door1)->GetChildActor());
	Door->bOpenDoor = true;

}

void ANPC1DoorRiddle::RightChoiceEvent() {
	APawnInteractiveClass* NPC = Cast<APawnInteractiveClass>(Cast<UChildActorComponent>(NPC1)->GetChildActor());
	NPC->SpeechContator += 2;
	NPC->Speak();
}

void ANPC1DoorRiddle::EndChoiceEvent(APawnInteractiveClass* SpokenActor) {
	ADoor* Door = Cast<ADoor>(Cast<UChildActorComponent>(Door1)->GetChildActor());
	APawnInteractiveClass* NPC = Cast<APawnInteractiveClass>(Cast<UChildActorComponent>(NPC1)->GetChildActor());
	if(!Door->bOpenDoor)
		NPC->QuestionAt = 1;
}

