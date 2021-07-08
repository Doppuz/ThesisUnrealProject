// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleWith2Doors.h"
#include "../Elements/Door.h"
#include "../Elements/PuzzleButton.h"
#include "../Elements/DestructibleElements.h"
#include "Components/BoxComponent.h"
#include "../GameModeTutorial.h"
#include "../GameInstance/BartleManagerGameInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APuzzleWith2Doors::APuzzleWith2Doors()
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

	PuzzleButtons = CreateDefaultSubobject<USceneComponent>(TEXT("PuzzleButtons"));
	PuzzleButtons->SetupAttachment(RootComponent);

	Puzzle1 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Puzzle1"));
	Puzzle1->SetupAttachment(PuzzleButtons);

	Puzzle2 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Puzzle2"));
	Puzzle2->SetupAttachment(PuzzleButtons);

	Puzzle3 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Puzzle3"));
	Puzzle3->SetupAttachment(PuzzleButtons);

	DestructibleGate = CreateDefaultSubobject<USceneComponent>(TEXT("DestrGates"));
	DestructibleGate->SetupAttachment(RootComponent);

	DestrGate1 = CreateDefaultSubobject<UChildActorComponent>(TEXT("DestrGate1"));
	DestrGate1->SetupAttachment(DestructibleGate);

	DestrGate2 = CreateDefaultSubobject<UChildActorComponent>(TEXT("DestrGate2"));
	DestrGate2->SetupAttachment(DestructibleGate);
}

// Called when the game starts or when spawned
void APuzzleWith2Doors::BeginPlay()
{
	Super::BeginPlay();
	
	APuzzleButton* Button1 = Cast<APuzzleButton>(Cast<UChildActorComponent>(Puzzle1)->GetChildActor());
	APuzzleButton* Button2 = Cast<APuzzleButton>(Cast<UChildActorComponent>(Puzzle2)->GetChildActor());
	APuzzleButton* Button3 = Cast<APuzzleButton>(Cast<UChildActorComponent>(Puzzle3)->GetChildActor());

	Button1->ButtonColor = GreyColor;
	Button2->ButtonColor = GreyColor;
	Button3->ButtonColor = GreyColor;

	Button1->Trigger->OnComponentBeginOverlap.AddDynamic(this,&APuzzleWith2Doors::OnOverlap);
	Button2->Trigger->OnComponentBeginOverlap.AddDynamic(this,&APuzzleWith2Doors::OnOverlap);
	Button3->Trigger->OnComponentBeginOverlap.AddDynamic(this,&APuzzleWith2Doors::OnOverlap);

	RightOrder.Add(Button2);
	RightOrder.Add(Button1);
	RightOrder.Add(Button3);

	ADestructibleElements* Gate = Cast<ADestructibleElements>(DestrGate1->GetChildActor());
	Gate->DestructionDelegate.AddDynamic(this,&APuzzleWith2Doors::DestructionEvent);
}

// Called every frame
void APuzzleWith2Doors::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APuzzleWith2Doors::CheckPuzzleActor() {
	
	if(RightOrder.Num() > MyOrder.Num())
		return;

	//Check the button's order.

	for(int i = 0; i < RightOrder.Num(); i++){
		if(RightOrder[i] != MyOrder[i]){

			for(APuzzleButton* Button : MyOrder){
				Button->Mesh->SetMaterial(0,RedColor);	
			}

		    MyOrder.Empty();	
            GetWorld()->GetTimerManager().SetTimer(ResetPuzzleTimer,this,&APuzzleWith2Doors::ResetPuzzle,0.5f,false);

			return;

		}
	}	

	//Color the buttons.

	for(APuzzleButton* Button : MyOrder){
        Button->Mesh->SetMaterial(0,GreenColor);	
	}

	//Change the healt of the gate so that it will never break.
	Cast<ADestructibleElements>(DestrGate1->GetChildActor())->DamageValue = 0;
	Cast<ADestructibleElements>(DestrGate2->GetChildActor())->DamageValue = 0;

	//Update Bartle's values
	UBartleManagerGameInstance* Bartle = Cast<UBartleManagerGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	Bartle->EquallyDistributedUpdate(Type::Explorer,Type::Killer);

	//Open the doors.
	ADoor* ActorDoor1 = Cast<ADoor>(Cast<UChildActorComponent>(Door1)->GetChildActor());
	ActorDoor1->bOpenDoor = true;	
	ADoor* ActorDoor2 = Cast<ADoor>(Cast<UChildActorComponent>(Door2)->GetChildActor());
	ActorDoor2->bOpenDoor = true;	
}

void APuzzleWith2Doors::ResetPuzzle() {
	
	for(APuzzleButton* Button : RightOrder){
		Button->Mesh->SetMaterial(0,nullptr);	
    	Button->bDisableOverlap = false;
	}

}

void APuzzleWith2Doors::OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit) {
	if(OtherActor->IsA(APawn::StaticClass())){

		if(Cast<APawn>(OtherActor)->GetController()->IsA(APlayerController::StaticClass())){
			if(!Cast<ADestructibleElements>(DestrGate1->GetChildActor())->bIAmDestroyed){
				if(!MyOrder.Contains(Cast<APuzzleButton>(Hit.GetActor()))){
					MyOrder.Add(Cast<APuzzleButton>(Hit.GetActor()));
					CheckPuzzleActor();
				}
			}
		}

	}
}

void APuzzleWith2Doors::DestructionEvent(ADestructibleElements* Elem) {
	
	//Update Bartle's values
	UBartleManagerGameInstance* Bartle = Cast<UBartleManagerGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	Bartle->EquallyDistributedUpdate(Type::Killer,Type::Explorer);

}

