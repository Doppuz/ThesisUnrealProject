// Fill out your copyright notice in the Description page of Project Settings.


#include "FifthPuzzle.h"
#include "../Elements/GeneralElements/Doors/Door.h"
#include "../Elements/Destructible/DestructibleElements.h"
#include "../Elements/GeneralElements/CoinController.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "../GameModeTutorial.h"
#include "Kismet/GameplayStatics.h"
#include "ShakeActor.h"
#include "Components/WidgetComponent.h"
#include "../UI/elements/OverlayedText.h"

// Sets default values
AFifthPuzzle::AFifthPuzzle()
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

	DestructibleGate = CreateDefaultSubobject<USceneComponent>(TEXT("DestrGates"));
	DestructibleGate->SetupAttachment(RootComponent);

	DestrGate1 = CreateDefaultSubobject<UChildActorComponent>(TEXT("DestrGate1"));
	DestrGate1->SetupAttachment(DestructibleGate);

	DestrGate2 = CreateDefaultSubobject<UChildActorComponent>(TEXT("DestrGate2"));
	DestrGate2->SetupAttachment(DestructibleGate);

	DestrGate3 = CreateDefaultSubobject<UChildActorComponent>(TEXT("DestrGate3"));
	DestrGate3->SetupAttachment(DestructibleGate);

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

	UI = CreateDefaultSubobject<USceneComponent>(TEXT("UI"));
	UI->SetupAttachment(RootComponent);

	OverlayedTextCoins = CreateDefaultSubobject<UWidgetComponent>(TEXT("OverlayedTextCoins"));
	OverlayedTextCoins->SetupAttachment(UI);

	OverlayedTextWall = CreateDefaultSubobject<UWidgetComponent>(TEXT("OverlayedTextWall"));
	OverlayedTextWall->SetupAttachment(UI);

	GatesDestructed = 0;
	CoinsCollected = 0;
}

// Called when the game starts or when spawned
void AFifthPuzzle::BeginPlay()
{
	Super::BeginPlay();

	//Set overlayed Text
	Cast<UOverlayedText>(OverlayedTextCoins->GetWidget())->SetText("Collects the coins OR ...");
	Cast<UOverlayedText>(OverlayedTextWall->GetWidget())->SetText("... OR Explore the Dungeon!");

	TArray<USceneComponent*> Gates;
	DestructibleGate->GetChildrenComponents(false,Gates);

	for(int i = 0; i < Gates.Num(); i++){
		AShakeActor* ShakeActor = Cast<AShakeActor>(Cast<UChildActorComponent>(Gates[i])->GetChildActor());
		Cast<ADestructibleElements>(ShakeActor->ShakingActor->GetChildActor())->DestructionDelegate.AddDynamic(this,&AFifthPuzzle::Destruction);
	}

	TArray<USceneComponent*> CoinsArray;
	Coins->GetChildrenComponents(false,CoinsArray);

	for(USceneComponent* Scene: CoinsArray){
		ACoinController* Coin = Cast<ACoinController>(Cast<UChildActorComponent>(Scene)->GetChildActor());
		Coin->CollectedDelegate.AddDynamic(this, &AFifthPuzzle::CoinCollected);
	}

}

// Called every frame
void AFifthPuzzle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFifthPuzzle::Destruction(ADestructibleElements* Elem) {
	
	ADoor* Door01 = Cast<ADoor>(Door1->GetChildActor());
	ADoor* Door03 = Cast<ADoor>(Door3->GetChildActor());

	if(!Door01->bOpenDoor){

		Door01->bOpenDoor = true;
		Door03->bOpenDoor = true;

		//Update Bartle's values
		
		AGameModeAbstract* GameMode = Cast<AGameModeAbstract>(GetWorld()->GetAuthGameMode());
		GameMode->Update->DistributedUpdate(Type::Explorer,Type::Achiever);

	}

	GatesDestructed += 1;
}

void AFifthPuzzle::CoinCollected() {
	ADoor* Door01 = Cast<ADoor>(Door1->GetChildActor());
	ADoor* Door02 = Cast<ADoor>(Door2->GetChildActor());
			
	if(!Door01->bOpenDoor){
	
		Door01->bOpenDoor = true;
		Door02->bOpenDoor = true;
	
		//Update Bartle's values
		AGameModeAbstract* GameMode = Cast<AGameModeAbstract>(GetWorld()->GetAuthGameMode());
		GameMode->Update->DistributedUpdate(Type::Achiever,Type::Explorer);

	}

	CoinsCollected += 1;
}

