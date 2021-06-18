// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC1Door.h"
#include "../Elements/Door.h"
#include "../Character/PawnInteractiveClass.h"
#include "Components/BoxComponent.h"
#include "../Character/CharacterPawnQuad.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ANPC1Door::ANPC1Door()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	
	Doors = CreateDefaultSubobject<USceneComponent>(TEXT("Doors"));
	Doors->SetupAttachment(RootComponent);

	Door1 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Door1"));
	Door1->SetChildActorClass(ADoor::StaticClass());
	Door1->SetupAttachment(Doors);
	Door1->SetWorldScale3D(FVector(1.2f,1.2f,1.f));

	NPCs = CreateDefaultSubobject<USceneComponent>(TEXT("NPCs"));
	NPCs->SetupAttachment(RootComponent);

	NPC1 = CreateDefaultSubobject<UChildActorComponent>(TEXT("NPC1"));
	NPC1->SetChildActorClass(APawnInteractiveClass::StaticClass());
	NPC1->SetupAttachment(NPCs);

	QuestionAt = 200;

}

// Called when the game starts or when spawned
void ANPC1Door::BeginPlay()
{
	Super::BeginPlay();

//---- Need to pass the parameter to the mesh because they are not exposed -----

	APawnInteractiveClass* NPC = Cast<APawnInteractiveClass>(Cast<UChildActorComponent>(NPC1)->GetChildActor());

	NPC->Speech = Speech;
	NPC->Questions = Questions;
	NPC->QuestionAt = QuestionAt;
	NPC->MeshToEquip = MeshToEquip;

	NPC->LeftChoice.AddDynamic(this,&ANPC1Door::LeftChoiceEvent);
	NPC->RightChoice.AddDynamic(this,&ANPC1Door::RightChoiceEvent);
	NPC->EndDialog.AddDynamic(this,&ANPC1Door::EndChoiceEvent);

}

// Called every frame
void ANPC1Door::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANPC1Door::LeftChoiceEvent() {
	ACharacterPawnQuad* PlayerPawn = Cast<ACharacterPawnQuad>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
	PlayerPawn->EquipmentMesh->SetStaticMesh(MeshToEquip);
	
	APawnInteractiveClass* NPC = Cast<APawnInteractiveClass>(Cast<UChildActorComponent>(NPC1)->GetChildActor());

	NPC->SpeechContator += 1;
	NPC->Speak();
	NPC->SpeechContator = NPC->Speech.Num() - 2;
}

void ANPC1Door::RightChoiceEvent() {
	APawnInteractiveClass* NPC = Cast<APawnInteractiveClass>(Cast<UChildActorComponent>(NPC1)->GetChildActor());
	NPC->SpeechContator += 2;
	NPC->Speak();
}

void ANPC1Door::EndChoiceEvent() {
	ADoor* Door = Cast<ADoor>(Cast<UChildActorComponent>(Door1)->GetChildActor());
	Door->bOpenDoor = true;
}
