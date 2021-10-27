// Fill out your copyright notice in the Description page of Project Settings.


#include "ThirdPuzzle.h"
#include "../Elements/GeneralElements/Doors/Door.h"
#include "../Elements/Destructible/DestructibleElements.h"
#include "../Elements/GeneralElements/CoinController.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "../GameModeTutorial.h"
#include "Kismet/GameplayStatics.h"
#include "../UI/Elements/OverlayedText.h"
#include "Components/WidgetComponent.h"
#include "../Elements/Destructible/GenericDestructibleElements.h"
#include "../Character/CharacterPawnQuad.h"

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

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Trigger->SetupAttachment(RootComponent);

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

	CoinsCollected = 0;
}

// Called when the game starts or when spawned
void AThirdPuzzle::BeginPlay()
{
	Super::BeginPlay();

	//Set overlayed Text
	Cast<UOverlayedText>(OverlayedTextWall->GetWidget())->SetText("You can explore this path OR ...");
	Cast<UOverlayedText>(OverlayedTextCoins->GetWidget())->SetText("... OR collect these coins.");

	TArray<USceneComponent*> CoinsArray;
	Coins->GetChildrenComponents(false,CoinsArray);

	for(USceneComponent* Scene: CoinsArray){
		ACoinController* Coin = Cast<ACoinController>(Cast<UChildActorComponent>(Scene)->GetChildActor());
		Coin->CollectedDelegate.AddDynamic(this, &AThirdPuzzle::CoinCollected);
	}

	Trigger->OnComponentBeginOverlap.AddDynamic(this,&AThirdPuzzle::OnOverlap);

}

// Called every frame
void AThirdPuzzle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AThirdPuzzle::CoinCollected() {
	
	//AGenericDestructibleElements* ShakeActor = Cast<AGenericDestructibleElements>(DestrGate1->GetChildActor());
	//if(Cast<AGenericDestructibleElements>(ShakeActor->ShakingActor->GetChildActor())->bSolved)
	//	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);

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
		GameMode->Update->EquallyDistributedUpdate(Type::Achiever,Type::Explorer);
	
	}

	CoinsCollected += 1;
}

void AThirdPuzzle::OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit){

	if(OtherActor->IsA(ACharacterPawnQuad::StaticClass())){
		
		FLatentActionInfo LatentInfo;
	    UGameplayStatics::LoadStreamLevel(this, TEXT("ThirdChoice"), true, false, LatentInfo);
		
		ADoor* Door01 = Cast<ADoor>(Door1->GetChildActor());
		ADoor* Door03 = Cast<ADoor>(Door3->GetChildActor());
		
		Door01->bClose = false;
			
		Door01->bOpenDoor = true;
		Door03->bOpenDoor = true;

		AGameModeTutorial* GameMode = Cast<AGameModeTutorial>(GetWorld()->GetAuthGameMode());

		//Update Bartle's values
		GameMode->Update->EquallyDistributedUpdate(Type::Explorer,Type::Achiever);

	}

}
