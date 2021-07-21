// Fill out your copyright notice in the Description page of Project Settings.


#include "ThirdPuzzle.h"
#include "../Elements/Door.h"
#include "../Elements/DestructibleElements.h"
#include "../Elements/CoinController.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "../GameModeTutorial.h"
#include "Kismet/GameplayStatics.h"
#include "../GameInstance/BartleManagerGameInstance.h"
#include "ShakeActor.h"
#include "Components/WidgetComponent.h"
#include "../UI/OverlayedText.h"

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
void AThirdPuzzle::BeginPlay()
{
	Super::BeginPlay();

	//Set overlayed Text
	Cast<UOverlayedText>(OverlayedTextWall->GetWidget())->SetText("Maybe you can destroy this wall OR ...");
	Cast<UOverlayedText>(OverlayedTextCoins->GetWidget())->SetText("... OR collect these coins.");

	TArray<USceneComponent*> Gates;
	DestructibleGate->GetChildrenComponents(false,Gates);

	for(int i = 0; i < Gates.Num(); i++){
		AShakeActor* ShakeActor = Cast<AShakeActor>(Cast<UChildActorComponent>(Gates[i])->GetChildActor());
		Cast<ADestructibleElements>(ShakeActor->ShakingActor->GetChildActor())->DestructionDelegate.AddDynamic(this,&AThirdPuzzle::Destruction);
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

	if(!Door01->bOpenDoor){

		Door01->bOpenDoor = true;
		Door03->bOpenDoor = true;
		
		FLatentActionInfo LatentInfo;
	    UGameplayStatics::LoadStreamLevel(this, TEXT("ThirdChoice"), true, false, LatentInfo);
		
		AGameModeTutorial* GameMode = Cast<AGameModeTutorial>(GetWorld()->GetAuthGameMode());
		
		if(!GameMode->Levels.Contains("ThirdChoice"))
			GameMode->Levels.Add("ThirdChoice");

		//Update Bartle's values
		UBartleManagerGameInstance* Bartle = Cast<UBartleManagerGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		Bartle->EquallyDistributedUpdate(Type::Explorer,Type::Achiever);
	
	}

	GatesDestructed += 1;
}

void AThirdPuzzle::CoinCollected() {
	
	AShakeActor* ShakeActor = Cast<AShakeActor>(DestrGate1->GetChildActor());
	if(Cast<ADestructibleElements>(ShakeActor->ShakingActor->GetChildActor())->bSolved)
		UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);

	ADoor* Door01 = Cast<ADoor>(Door1->GetChildActor());
	ADoor* Door02 = Cast<ADoor>(Door2->GetChildActor());

	if(!Door01->bOpenDoor){

		Door01->bClose = false;
			
		Door01->bOpenDoor = true;
		Door02->bOpenDoor = true;

		FLatentActionInfo LatentInfo;
	    UGameplayStatics::LoadStreamLevel(this, TEXT("ThirdChoice"), true, false, LatentInfo);

		AGameModeTutorial* GameMode = Cast<AGameModeTutorial>(GetWorld()->GetAuthGameMode());
		
		if(!GameMode->Levels.Contains("ThirdChoice"))
			GameMode->Levels.Add("ThirdChoice");

		//Update Bartle's values
		UBartleManagerGameInstance* Bartle = Cast<UBartleManagerGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		Bartle->EquallyDistributedUpdate(Type::Achiever,Type::Explorer);
	
	}

	CoinsCollected += 1;
}

