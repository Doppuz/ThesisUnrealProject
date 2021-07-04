// Fill out your copyright notice in the Description page of Project Settings.


#include "ForthPuzzle.h"
#include "../Elements/Door.h"
#include "../Elements/PuzzleButton.h"
#include "../Character/PawnInteractiveClass.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "../GameModeTutorial.h"
#include "Kismet/GameplayStatics.h"
#include "../GameInstance/BartleManagerGameInstance.h"

// Sets default values
AForthPuzzle::AForthPuzzle()
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
	NPC1->SetupAttachment(NPCs);

	NPC2 = CreateDefaultSubobject<UChildActorComponent>(TEXT("NPC2"));
	NPC2->SetupAttachment(NPCs);

	NPC3 = CreateDefaultSubobject<UChildActorComponent>(TEXT("NPC3"));
	NPC3->SetupAttachment(NPCs);

	NPC4 = CreateDefaultSubobject<UChildActorComponent>(TEXT("NPC4"));
	NPC4->SetupAttachment(NPCs);

	PuzzleButtons = CreateDefaultSubobject<USceneComponent>(TEXT("PuzzleButtons"));
	PuzzleButtons->SetupAttachment(RootComponent);

	Puzzle1 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Puzzle1"));
	Puzzle1->SetupAttachment(PuzzleButtons);

	Puzzle2 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Puzzle2"));
	Puzzle2->SetupAttachment(PuzzleButtons);
	
	Puzzle3 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Puzzle3"));
	Puzzle3->SetupAttachment(PuzzleButtons);

	Puzzle4 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Puzzle4"));
	Puzzle4->SetupAttachment(PuzzleButtons);

	SpokenAllies = 0;
	PuzzleCount = 0;

}

// Called when the game starts or when spawned
void AForthPuzzle::BeginPlay()
{
	Super::BeginPlay();

	TArray<USceneComponent*> NPCArray;
	NPCs->GetChildrenComponents(false,NPCArray);

	for(int i = 0; i < NPCArray.Num(); i++){
		APawnInteractiveClass* NPC = Cast<APawnInteractiveClass>(Cast<UChildActorComponent>(NPCArray[i])->GetChildActor());
		NPC->EndDialog.AddDynamic(this,&AForthPuzzle::SpokenAlliesEvent);
	}

	TArray<USceneComponent*> PuzzleButtonsArray;
	PuzzleButtons->GetChildrenComponents(false,PuzzleButtonsArray);

	for(USceneComponent* Scene: PuzzleButtonsArray){
		APuzzleButton* Button = Cast<APuzzleButton>(Cast<UChildActorComponent>(Scene)->GetChildActor());
		Button->Trigger->OnComponentBeginOverlap.AddDynamic(this, &AForthPuzzle::OnOverlap);
	}

}

// Called every frame
void AForthPuzzle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AForthPuzzle::SpokenAlliesEvent(APawnInteractiveClass* SpokenActor) {
	
	if(!SpokenActor->bAlreadySpoken)
		SpokenAllies += 1;
	
	if(SpokenAllies == 4 && PuzzleCount != 4){
		ADoor* Door01 = Cast<ADoor>(Door1->GetChildActor());
		Door01->bOpenDoor = true;
		
		FLatentActionInfo LatentInfo;
		UGameplayStatics::LoadStreamLevel(this, TEXT("FifthChoice"), true, false, LatentInfo);

		AGameModeTutorial* GameMode = Cast<AGameModeTutorial>(GetWorld()->GetAuthGameMode());
		GameMode->Levels.Add("FifthChoice");

		//Update Bartle's values
		UBartleManagerGameInstance* Bartle = Cast<UBartleManagerGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		Bartle->DistributedUpdate(Type::Socializer,Type::Explorer);

		SpokenAllies = -1;
		PuzzleCount = -1;
	}


}

void AForthPuzzle::OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit) {
	
	if(OtherActor->IsA(APawn::StaticClass())){

		if(Cast<APawn>(OtherActor)->GetController()->IsA(APlayerController::StaticClass())){
			
			if(!Cast<APuzzleButton>(Hit.GetActor())->bIsPressed){
				PuzzleCount += 1;

				if(PuzzleCount == 4 && SpokenAllies != 4){
					
					ADoor* Door01 = Cast<ADoor>(Door1->GetChildActor());
					Door01->bOpenDoor = true;
					
					FLatentActionInfo LatentInfo;
					UGameplayStatics::LoadStreamLevel(this, TEXT("FifthChoice"), true, false, LatentInfo);

					AGameModeTutorial* GameMode = Cast<AGameModeTutorial>(GetWorld()->GetAuthGameMode());
					GameMode->Levels.Add("FifthChoice");

					//Update Bartle's values
					UBartleManagerGameInstance* Bartle = Cast<UBartleManagerGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
					Bartle->DistributedUpdate(Type::Explorer,Type::Socializer);

					SpokenAllies = -1;
					PuzzleCount = -1;

				}

				Cast<APuzzleButton>(Hit.GetActor())->bIsPressed = true;
			
			}
		}

	}

}
