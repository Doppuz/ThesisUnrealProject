// Fill out your copyright notice in the Description page of Project Settings.


#include "LastPuzzle.h"
#include "../Elements/Door.h"
#include "../Elements/PuzzleButton.h"
#include "../Character/PawnInteractiveClass.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "../Elements/DestructibleElements.h"
#include "../Elements/CoinController.h"
#include "../GameModeTutorial.h"
#include "Kismet/GameplayStatics.h"
#include "../GameInstance/BartleManagerGameInstance.h"
#include "Components/WidgetComponent.h"
#include "../UI/OverlayedText.h"

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

	UI = CreateDefaultSubobject<USceneComponent>(TEXT("UI"));
	UI->SetupAttachment(RootComponent);

	OverlayedTextCoins = CreateDefaultSubobject<UWidgetComponent>(TEXT("OverlayedTextCoins"));
	OverlayedTextCoins->SetupAttachment(UI);

	OverlayedTextWall = CreateDefaultSubobject<UWidgetComponent>(TEXT("OverlayedTextWall"));
	OverlayedTextWall->SetupAttachment(UI);

	SpokenAllies = 0;
	CoinsCollected = 0;

}

// Called when the game starts or when spawned
void ALastPuzzle::BeginPlay()
{
	Super::BeginPlay();

	//Set overlayed Text
	Cast<UOverlayedText>(OverlayedTextWall->GetWidget())->SetText("Hit the boxes OR ...");
	Cast<UOverlayedText>(OverlayedTextCoins->GetWidget())->SetText("... OR talk to everyone.");

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

	if(SpokenAllies == 0){
		DestrGate1->DestroyChildActor();
		DestrGate2->DestroyChildActor();
	}
	
	if(!SpokenActor->bAlreadySpoken)
		SpokenAllies += 1;
	
	if(SpokenAllies == 2 && CoinsCollected != 2){

		ADoor* Door01 = Cast<ADoor>(Door1->GetChildActor());
		Door01->bOpenDoor = true;

		//Update Bartle's values
		UBartleManagerGameInstance* Bartle = Cast<UBartleManagerGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		Bartle->DistributedUpdate(Type::Socializer,Type::Achiever);

	}


}

void ALastPuzzle::Destruction(ADestructibleElements* Elem) {

	if(CoinsCollected == 0){
		
		NPC1->DestroyChildActor();
		NPC2->DestroyChildActor();

	}
	
	FRotator Rotation = FRotator(0,0,0);
	ACoinController* Coin = GetWorld()->SpawnActor<ACoinController>(CoinClass,Elem->GetActorLocation(),Rotation);
	Coin->SetActorScale3D(FVector(0.5f,0.5f,0.5f));
	Coin->CollectedDelegate.AddDynamic(this, &ALastPuzzle::CoinCollected);
	
}

void ALastPuzzle::CoinCollected() {
	CoinsCollected += 1;

	if(CoinsCollected == 2 && SpokenAllies != 2){

		ADoor* Door01 = Cast<ADoor>(Door1->GetChildActor());
		Door01->bOpenDoor = true;

		//Update Bartle's values
		UBartleManagerGameInstance* Bartle = Cast<UBartleManagerGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		Bartle->DistributedUpdate(Type::Achiever,Type::Socializer);

	}
}

