// Fill out your copyright notice in the Description page of Project Settings.


#include "SecondPuzzle.h"
#include "../Elements/Door.h"
#include "../Character/CharacterPawnQuad.h"
#include "../Character/PawnInteractiveClass.h"
#include "../Character/PawnInteractiveMove.h"
#include "Components/BoxComponent.h"
#include "../GameModeTutorial.h"
#include "../Elements/ActorSpawner.h"
#include "Kismet/GameplayStatics.h"
#include "../GameInstance/BartleManagerGameInstance.h"

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

	Door5 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Door5"));
	Door5->SetupAttachment(Doors);
	Door5->SetWorldScale3D(FVector(1.2f,1.2f,1.f));

	Enemies = CreateDefaultSubobject<USceneComponent>(TEXT("Enemies"));
	Enemies->SetupAttachment(RootComponent);

	SpawnEnemy1 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Enemy1"));
	SpawnEnemy1->SetupAttachment(Enemies);

	SpawnEnemy2 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Enemy2"));
	SpawnEnemy2->SetupAttachment(Enemies);

	SpawnEnemy3 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Enemy3"));
	SpawnEnemy3->SetupAttachment(Enemies);

	NPCs = CreateDefaultSubobject<USceneComponent>(TEXT("NPCs"));
	NPCs->SetupAttachment(RootComponent);

	NPC1 = CreateDefaultSubobject<UChildActorComponent>(TEXT("NPC1"));
	NPC1->SetupAttachment(NPCs);
	
	SpawnNPC2 = CreateDefaultSubobject<UChildActorComponent>(TEXT("NPC2"));
	SpawnNPC2->SetupAttachment(NPCs);

	SpawnNPC3 = CreateDefaultSubobject<UChildActorComponent>(TEXT("NPC3"));
	SpawnNPC3->SetupAttachment(NPCs);

	SpawnNPC4 = CreateDefaultSubobject<UChildActorComponent>(TEXT("NPC4"));
	SpawnNPC4->SetupAttachment(NPCs);

	DeathEnemies = 0;
	SpokenAllies = 0;
}

// Called when the game starts or when spawned
void ASecondPuzzle::BeginPlay()
{
	Super::BeginPlay();

	APawnInteractiveClass* NPCDoors = Cast<APawnInteractiveClass>(NPC1->GetChildActor());

	AActorSpawner* NPC02 = Cast<AActorSpawner>(SpawnNPC2->GetChildActor());
	AActorSpawner* NPC03 = Cast<AActorSpawner>(SpawnNPC3->GetChildActor());
	AActorSpawner* NPC04 = Cast<AActorSpawner>(SpawnNPC4->GetChildActor());
	
	AActorSpawner* Enemy01 = Cast<AActorSpawner>(SpawnEnemy1->GetChildActor());
	AActorSpawner* Enemy02 = Cast<AActorSpawner>(SpawnEnemy2->GetChildActor());
	AActorSpawner* Enemy03 = Cast<AActorSpawner>(SpawnEnemy3->GetChildActor());

	Cast<ACharacterPawnQuad>(Enemy01->SpawnActor())->End.AddDynamic(this,&ASecondPuzzle::EndEnemiesEvent);
	Cast<ACharacterPawnQuad>(Enemy02->SpawnActor())->End.AddDynamic(this,&ASecondPuzzle::EndEnemiesEvent);
	Cast<ACharacterPawnQuad>(Enemy03->SpawnActor())->End.AddDynamic(this,&ASecondPuzzle::EndEnemiesEvent);

	Cast<APawnInteractiveMove>(NPC02->SpawnActor())->EndDialog.AddDynamic(this,&ASecondPuzzle::SpokenAlliesEvent);
	Cast<APawnInteractiveMove>(NPC03->SpawnActor())->EndDialog.AddDynamic(this,&ASecondPuzzle::SpokenAlliesEvent);
	Cast<APawnInteractiveMove>(NPC04->SpawnActor())->EndDialog.AddDynamic(this,&ASecondPuzzle::SpokenAlliesEvent);
	

	NPCDoors->LeftChoice.AddDynamic(this,&ASecondPuzzle::LeftChoiceEvent);
	NPCDoors->RightChoice.AddDynamic(this,&ASecondPuzzle::RightChoiceEvent);

}

// Called every frame
void ASecondPuzzle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASecondPuzzle::LeftChoiceEvent() {
	Cast<ADoor>(Door1->GetChildActor())->bOpenDoor = true;
	Cast<ADoor>(Door2->GetChildActor())->bOpenDoor = true;	

	//Update Bartle's values
	UBartleManagerGameInstance* Bartle = Cast<UBartleManagerGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	Bartle->EquallyDistributedUpdate(Type::Killer,Type::Socializer);
	
	APawnInteractiveClass* NPC = Cast<APawnInteractiveClass>(NPC1->GetChildActor());
	NPC->SpeechContator += 2;
	NPC->Speak();
}

void ASecondPuzzle::RightChoiceEvent() {
	Cast<ADoor>(Door3->GetChildActor())->bOpenDoor = true;
	Cast<ADoor>(Door4->GetChildActor())->bOpenDoor = true;

	//Update Bartle's values
	UBartleManagerGameInstance* Bartle = Cast<UBartleManagerGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	Bartle->EquallyDistributedUpdate(Type::Socializer,Type::Killer);
	
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

