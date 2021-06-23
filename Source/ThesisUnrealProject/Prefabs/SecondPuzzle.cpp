// Fill out your copyright notice in the Description page of Project Settings.


#include "SecondPuzzle.h"
#include "../Elements/Door.h"
#include "../Character/CharacterPawnQuad.h"
#include "../Character/PawnInteractiveClass.h"
#include "../Character/PawnInteractiveMove.h"
#include "Components/BoxComponent.h"
#include "../GameModeTutorial.h"

// Sets default values
ASecondPuzzle::ASecondPuzzle()
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

	Door2 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Door2"));
	Door2->SetChildActorClass(ADoor::StaticClass());
	Door2->SetupAttachment(Doors);
	Door2->SetWorldScale3D(FVector(1.2f,1.2f,1.f));

	Door3 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Door3"));
	Door3->SetChildActorClass(ADoor::StaticClass());
	Door3->SetupAttachment(Doors);
	Door3->SetWorldScale3D(FVector(1.2f,1.2f,1.f));

	Door4 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Door4"));
	Door4->SetChildActorClass(ADoor::StaticClass());
	Door4->SetupAttachment(Doors);
	Door4->SetWorldScale3D(FVector(1.2f,1.2f,1.f));

	Door5 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Door5"));
	Door5->SetChildActorClass(ADoor::StaticClass());
	Door5->SetupAttachment(Doors);
	Door5->SetWorldScale3D(FVector(1.2f,1.2f,1.f));

	Enemies = CreateDefaultSubobject<USceneComponent>(TEXT("Enemies"));
	Enemies->SetupAttachment(RootComponent);

	Enemy1 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Enemy1"));
	Enemy1->SetChildActorClass(ACharacterPawnQuad::StaticClass());
	Enemy1->SetupAttachment(Enemies);

	Enemy2 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Enemy2"));
	Enemy2->SetChildActorClass(ACharacterPawnQuad::StaticClass());
	Enemy2->SetupAttachment(Enemies);

	Enemy3 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Enemy3"));
	Enemy3->SetChildActorClass(ACharacterPawnQuad::StaticClass());
	Enemy3->SetupAttachment(Enemies);

	NPCs = CreateDefaultSubobject<USceneComponent>(TEXT("NPCs"));
	NPCs->SetupAttachment(RootComponent);

	NPC1 = CreateDefaultSubobject<UChildActorComponent>(TEXT("NPC1"));
	NPC1->SetChildActorClass(APawnInteractiveClass::StaticClass());
	NPC1->SetupAttachment(NPCs);
	
	NPC2 = CreateDefaultSubobject<UChildActorComponent>(TEXT("NPC2"));
	NPC2->SetChildActorClass(APawnInteractiveMove::StaticClass());
	NPC2->SetupAttachment(NPCs);

	NPC3 = CreateDefaultSubobject<UChildActorComponent>(TEXT("NPC3"));
	NPC3->SetChildActorClass(APawnInteractiveMove::StaticClass());
	NPC3->SetupAttachment(NPCs);

	NPC4 = CreateDefaultSubobject<UChildActorComponent>(TEXT("NPC4"));
	NPC4->SetChildActorClass(APawnInteractiveMove::StaticClass());
	NPC4->SetupAttachment(NPCs);

	DeathEnemies = 0;
	SpokenAllies = 0;
}

// Called when the game starts or when spawned
void ASecondPuzzle::BeginPlay()
{
	Super::BeginPlay();

	APawnInteractiveClass* NPCDoors = Cast<APawnInteractiveClass>(NPC1->GetChildActor());

	APawnInteractiveMove* NPC02 = Cast<APawnInteractiveMove>(NPC2->GetChildActor());
	APawnInteractiveMove* NPC03 = Cast<APawnInteractiveMove>(NPC3->GetChildActor());
	APawnInteractiveMove* NPC04 = Cast<APawnInteractiveMove>(NPC4->GetChildActor());
	
	ACharacterPawnQuad* Enemy01 = Cast<ACharacterPawnQuad>(Enemy1->GetChildActor());
	ACharacterPawnQuad* Enemy02 = Cast<ACharacterPawnQuad>(Enemy2->GetChildActor());
	ACharacterPawnQuad* Enemy03 = Cast<ACharacterPawnQuad>(Enemy3->GetChildActor());

	NPC02->EndDialog.AddDynamic(this,&ASecondPuzzle::SpokenAlliesEvent);
	NPC03->EndDialog.AddDynamic(this,&ASecondPuzzle::SpokenAlliesEvent);
	NPC04->EndDialog.AddDynamic(this,&ASecondPuzzle::SpokenAlliesEvent);

	Enemy01->End.AddDynamic(this,&ASecondPuzzle::EndEnemiesEvent);
	Enemy02->End.AddDynamic(this,&ASecondPuzzle::EndEnemiesEvent);
	Enemy03->End.AddDynamic(this,&ASecondPuzzle::EndEnemiesEvent);

	NPCDoors->LeftChoice.AddDynamic(this,&ASecondPuzzle::LeftChoiceEvent);
	NPCDoors->RightChoice.AddDynamic(this,&ASecondPuzzle::RightChoiceEvent);

}

// Called every frame
void ASecondPuzzle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASecondPuzzle::CheckPuzzleActor() {
	
	
}

void ASecondPuzzle::LeftChoiceEvent() {
	Cast<ADoor>(Door1->GetChildActor())->bOpenDoor = true;
	Cast<ADoor>(Door2->GetChildActor())->bOpenDoor = true;	

	//Update Bartle's values
	AGameModeTutorial* GameMode = Cast<AGameModeTutorial>(GetWorld()->GetAuthGameMode());
	GameMode->EquallyDistributedUpdate(Type::Killer,Type::Socializer);
	
	APawnInteractiveClass* NPC = Cast<APawnInteractiveClass>(NPC1->GetChildActor());
	NPC->SpeechContator += 2;
	NPC->Speak();
}

void ASecondPuzzle::RightChoiceEvent() {
	Cast<ADoor>(Door3->GetChildActor())->bOpenDoor = true;
	Cast<ADoor>(Door4->GetChildActor())->bOpenDoor = true;

	//Update Bartle's values
	AGameModeTutorial* GameMode = Cast<AGameModeTutorial>(GetWorld()->GetAuthGameMode());
	GameMode->EquallyDistributedUpdate(Type::Socializer,Type::Killer);
	
	APawnInteractiveClass* NPC = Cast<APawnInteractiveClass>(NPC1->GetChildActor());
	NPC->SpeechContator += 2;
	NPC->Speak();
}

void ASecondPuzzle::EndEnemiesEvent() {
	
	DeathEnemies += 1;
	Cast<ADoor>(Door5->GetChildActor())->bOpenDoor = true;

}

void ASecondPuzzle::SpokenAlliesEvent(APawnInteractiveClass* SpokenActor) {
	
	if(!SpokenActor->bAlreadySpoken){
		SpokenAllies += 1;
		Cast<ADoor>(Door5->GetChildActor())->bOpenDoor = true;
	}
	
}

