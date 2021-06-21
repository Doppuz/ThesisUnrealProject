// Fill out your copyright notice in the Description page of Project Settings.


#include "LastPuzzle.h"
#include "../Elements/Door.h"
#include "../Elements/PuzzleButton.h"
#include "../Character/PawnInteractiveClass.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "../Elements/DestructibleElements.h"
#include "../Elements/CoinController.h"

// Sets default values
ALastPuzzle::ALastPuzzle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Doors = CreateDefaultSubobject<USceneComponent>(TEXT("Doors"));
	Doors->SetupAttachment(RootComponent);

	Door1 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Door1"));
	Door1->SetupAttachment(Doors);

	NPCs = CreateDefaultSubobject<USceneComponent>(TEXT("NPCs"));
	NPCs->SetupAttachment(RootComponent);

	NPC1 = CreateDefaultSubobject<UChildActorComponent>(TEXT("NPC1"));
	NPC1->SetupAttachment(NPCs);

	NPC2 = CreateDefaultSubobject<UChildActorComponent>(TEXT("NPC2"));
	NPC2->SetupAttachment(NPCs);

	DestructibleGate = CreateDefaultSubobject<USceneComponent>(TEXT("DestructibleGate"));
	DestructibleGate->SetupAttachment(RootComponent);

	DestrGate1 = CreateDefaultSubobject<UChildActorComponent>(TEXT("DestrGate1"));
	DestrGate1->SetupAttachment(DestructibleGate);

	DestrGate2 = CreateDefaultSubobject<UChildActorComponent>(TEXT("DestrGate2"));
	DestrGate2->SetupAttachment(DestructibleGate);

	SpokenAllies = 0;
	CoinsCollected = 0;

}

// Called when the game starts or when spawned
void ALastPuzzle::BeginPlay()
{
	Super::BeginPlay();

	TArray<USceneComponent*> NPCArray;
	NPCs->GetChildrenComponents(false,NPCArray);

	for(int i = 0; i < NPCArray.Num(); i++){
		APawnInteractiveClass* NPC = Cast<APawnInteractiveClass>(Cast<UChildActorComponent>(NPCArray[i])->GetChildActor());
		NPC->EndDialog.AddDynamic(this,&ALastPuzzle::SpokenAlliesEvent);
	}

	TArray<USceneComponent*> Gates;
	DestructibleGate->GetChildrenComponents(false,Gates);

	for(int i = 0; i < Gates.Num(); i++){
		ADestructibleElements* Gate = Cast<ADestructibleElements>(Cast<UChildActorComponent>(Gates[i])->GetChildActor());
		Gate->DestructionDelegate.AddDynamic(this,&ALastPuzzle::Destruction);
	}

}

// Called every frame
void ALastPuzzle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALastPuzzle::SpokenAlliesEvent(APawnInteractiveClass* SpokenActor) {
	
	if(!SpokenActor->bAlreadySpoken)
		SpokenAllies += 1;
	
	if(SpokenAllies == 2){
		ADoor* Door01 = Cast<ADoor>(Door1->GetChildActor());
		Door01->bOpenDoor = true;
	}


}

void ALastPuzzle::Destruction(ADestructibleElements* Elem) {
	
	FRotator Rotation = FRotator(0,0,0);
	ACoinController* Coin = GetWorld()->SpawnActor<ACoinController>(CoinClass,Elem->GetActorLocation(),Rotation);
	Coin->SetActorScale3D(FVector(0.5f,0.5f,0.5f));
	Coin->CollectedDelegate.AddDynamic(this, &ALastPuzzle::CoinCollected);
	
}

void ALastPuzzle::CoinCollected() {
	CoinsCollected += 1;

	if(CoinsCollected == 2){
		ADoor* Door01 = Cast<ADoor>(Door1->GetChildActor());
		Door01->bOpenDoor = true;
	}
}

