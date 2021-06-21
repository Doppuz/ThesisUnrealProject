// Fill out your copyright notice in the Description page of Project Settings.


#include "ThirdPuzzle.h"
#include "../Elements/Door.h"
#include "../Elements/DestructibleElements.h"
#include "../Elements/CoinController.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AThirdPuzzle::AThirdPuzzle()
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

	DestructibleGate = CreateDefaultSubobject<USceneComponent>(TEXT("DestrGates"));
	DestructibleGate->SetupAttachment(RootComponent);

	DestrGate1 = CreateDefaultSubobject<UChildActorComponent>(TEXT("DestrGate1"));
	DestrGate1->SetupAttachment(DestructibleGate);

	DestrGate2 = CreateDefaultSubobject<UChildActorComponent>(TEXT("DestrGate2"));
	DestrGate2->SetupAttachment(DestructibleGate);

	DestrGate3 = CreateDefaultSubobject<UChildActorComponent>(TEXT("DestrGate3"));
	DestrGate3->SetupAttachment(DestructibleGate);

	DestrGate4 = CreateDefaultSubobject<UChildActorComponent>(TEXT("DestrGate4"));
	DestrGate4->SetupAttachment(DestructibleGate);

	DestrGate5 = CreateDefaultSubobject<UChildActorComponent>(TEXT("DestrGate5"));
	DestrGate5->SetupAttachment(DestructibleGate);
		
	DestrGate6 = CreateDefaultSubobject<UChildActorComponent>(TEXT("DestrGate6"));
	DestrGate6->SetupAttachment(DestructibleGate);

	Coins = CreateDefaultSubobject<USceneComponent>(TEXT("Coins"));
	Coins->SetupAttachment(RootComponent);

	Coin1 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Coin1"));
	Coin1->SetupAttachment(Coins);

	Coin2 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Coin2"));
	Coin2->SetupAttachment(Coins);
	
	Coin3 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Coin3"));
	Coin3->SetupAttachment(Coins);

	Coin4 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Coin4"));
	Coin4->SetupAttachment(Coins);

	Coin5 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Coin5"));
	Coin5->SetupAttachment(Coins);

	Coin6 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Coin6"));
	Coin6->SetupAttachment(Coins);

	GatesDestructed = 0;
	CoinsCollected = 0;
}

// Called when the game starts or when spawned
void AThirdPuzzle::BeginPlay()
{
	Super::BeginPlay();

	TArray<USceneComponent*> Gates;
	DestructibleGate->GetChildrenComponents(false,Gates);

	for(int i = 0; i < Gates.Num(); i++){
		UE_LOG(LogTemp,Warning,TEXT("%i"),i);
		ADestructibleElements* Gate = Cast<ADestructibleElements>(Cast<UChildActorComponent>(Gates[i])->GetChildActor());
		Gate->DestructionDelegate.AddDynamic(this,&AThirdPuzzle::Destruction);
	}

	TArray<USceneComponent*> CoinsArray;
	Coins->GetChildrenComponents(false,CoinsArray);

	for(USceneComponent* Scene: CoinsArray){
		ACoinController* Coin = Cast<ACoinController>(Cast<UChildActorComponent>(Scene)->GetChildActor());
		Coin->CollectedDelegate.AddDynamic(this, &AThirdPuzzle::CoinCollected);
	}

}

// Called every frame
void AThirdPuzzle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AThirdPuzzle::Destruction(ADestructibleElements* Elem) {
	
	ADoor* Door01 = Cast<ADoor>(Door1->GetChildActor());
	ADoor* Door03 = Cast<ADoor>(Door3->GetChildActor());

	Door01->bOpenDoor = true;
	Door03->bOpenDoor = true;

	GatesDestructed += 1;
}

void AThirdPuzzle::CoinCollected() {
	ADoor* Door01 = Cast<ADoor>(Door1->GetChildActor());
	ADoor* Door02 = Cast<ADoor>(Door2->GetChildActor());

	Door01->bClose = false;
			
	Door01->bOpenDoor = true;
	Door02->bOpenDoor = true;

	CoinsCollected += 1;
}

