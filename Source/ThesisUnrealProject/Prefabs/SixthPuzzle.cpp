// Fill out your copyright notice in the Description page of Project Settings.


#include "SixthPuzzle.h"
#include "../Elements/GeneralElements/Doors/Door.h"
#include "Components/BoxComponent.h"
#include "../Elements/Puzzle/PuzzleButton.h"
#include "../Elements/Platforms/FallenPlatform.h"
#include "../Character/CharacterPawnQuad.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SpotLightComponent.h"
#include "../GameModeTutorial.h"
#include "../UI/Elements/OverlayedText.h"
#include "Components/WidgetComponent.h"
#include "ShakeActorFallen.h"

// Sets default values
ASixthPuzzle::ASixthPuzzle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
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
	
	PuzzleButtons = CreateDefaultSubobject<USceneComponent>(TEXT("PuzzleButtons"));
	PuzzleButtons->SetupAttachment(RootComponent);

	Puzzle1 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Puzzle1"));
	Puzzle1->SetupAttachment(PuzzleButtons);

	FallenPlatforms = CreateDefaultSubobject<USceneComponent>(TEXT("FallenPlatforms"));
	FallenPlatforms->SetupAttachment(RootComponent);

	FallenPlatform1 = CreateDefaultSubobject<UChildActorComponent>(TEXT("FallenPlatform1"));
	FallenPlatform1->SetupAttachment(FallenPlatforms);

	Triggers = CreateDefaultSubobject<USceneComponent>(TEXT("Triggers"));
	Triggers->SetupAttachment(RootComponent);

	Trigger1 = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger1"));
	Trigger1->SetupAttachment(Triggers);
	Trigger1->OnComponentBeginOverlap.AddDynamic(this, &ASixthPuzzle::OnOverlapStart);

	Trigger2 = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger2"));
	Trigger2->SetupAttachment(Triggers);
	Trigger2->OnComponentBeginOverlap.AddDynamic(this, &ASixthPuzzle::OnOverlapEnd);

	UI = CreateDefaultSubobject<USceneComponent>(TEXT("UI"));
	UI->SetupAttachment(RootComponent);

	OverlayedTextCoins = CreateDefaultSubobject<UWidgetComponent>(TEXT("OverlayedTextCoins"));
	OverlayedTextCoins->SetupAttachment(UI);

	OverlayedTextWall = CreateDefaultSubobject<UWidgetComponent>(TEXT("OverlayedTextWall"));
	OverlayedTextWall->SetupAttachment(UI);

}

// Called when the game starts or when spawned
void ASixthPuzzle::BeginPlay()
{
	Super::BeginPlay();

	//Set overlayed Text
	Cast<UOverlayedText>(OverlayedTextCoins->GetWidget())->SetText("Cross the platforms OR ...");
	Cast<UOverlayedText>(OverlayedTextCoins->GetWidget())->SetColor(FLinearColor(0.f,0.f,0.f,1.f));
	Cast<UOverlayedText>(OverlayedTextWall->GetWidget())->SetText("... OR enjoy a dark exploration.");

	AFallenPlatform* FallenPlat = Cast<AFallenPlatform>(Cast<AShakeActorFallen>(FallenPlatform1->GetChildActor())->ShakingActor->GetChildActor());

	
	APuzzleButton* Button = Cast<APuzzleButton>(Puzzle1->GetChildActor());
	Button->Trigger->OnComponentBeginOverlap.AddDynamic(this, &ASixthPuzzle::PuzzleOverlap);

	FallenPlat->FallenDelegate.AddDynamic(this, &ASixthPuzzle::FallenEvent);

}

/*void ASixthPuzzle::EndPlay(EEndPlayReason::Type Reason) {
	Trigger1->OnComponentBeginOverlap.RemoveDynamic(this, &ASixthPuzzle::OnOverlapStart);

	AFallenPlatform* FallenPlat = Cast<AFallenPlatform>(FallenPlatform1->GetChildActor());
	FallenPlat->FallenDelegate.RemoveDynamic(this, &ASixthPuzzle::FallenEvent);
}*/

void ASixthPuzzle::OnOverlapStart(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit) {
	
	if(OtherActor->IsA(ACharacterPawnQuad::StaticClass())){
		ACharacterPawnQuad* MyPawn = Cast<ACharacterPawnQuad>(OtherActor);
		
		if(MyPawn->GetController()->IsA(APlayerController::StaticClass())){
    		
			FLatentActionInfo LatentInfo;	
			UGameplayStatics::UnloadStreamLevel(this, TEXT("Day"), LatentInfo, true);
			MyPawn->SpotLight->Intensity = 100000.f;	

			//Close the doors.
			ADoor* Door01 = Cast<ADoor>(Cast<UChildActorComponent>(Door1)->GetChildActor());
			ADoor* Door02 = Cast<ADoor>(Door2->GetChildActor());

			if(!Door01->bOpenDoor){
		
				Door01->bOpenDoor = true;
				Door02->bOpenDoor = true;
		
				//Update Bartle's values
				AGameModeAbstract* GameMode = Cast<AGameModeAbstract>(GetWorld()->GetAuthGameMode());
				GameMode->Update->DistributedUpdate(Type::Explorer,Type::Killer);
		
			}
		}
	}
	
}

void ASixthPuzzle::OnOverlapEnd(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit) {
	
	if(OtherActor->IsA(ACharacterPawnQuad::StaticClass())){
		ACharacterPawnQuad* MyPawn = Cast<ACharacterPawnQuad>(OtherActor);
		
		if(MyPawn->GetController()->IsA(APlayerController::StaticClass())){
    		
			FLatentActionInfo LatentInfo;
			MyPawn->SpotLight->Intensity = 0.f;	
			UGameplayStatics::LoadStreamLevel(this, TEXT("Day"), true, true, LatentInfo);

		}
	}

}

void ASixthPuzzle::PuzzleOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit) {
	
	if(OtherActor->IsA(APawn::StaticClass())){

		if(Cast<APawn>(OtherActor)->GetController()->IsA(APlayerController::StaticClass())){

			ADoor* Door03 = Cast<ADoor>(Door3->GetChildActor());
			Door03->bOpenDoor = true;

		}

	}

}

void ASixthPuzzle::FallenEvent() {
	
	ADoor* Door01 = Cast<ADoor>(Door1->GetChildActor());
	Door01->bOpenDoor = true;
	
	//Update Bartle's values
	AGameModeAbstract* GameMode = Cast<AGameModeAbstract>(GetWorld()->GetAuthGameMode());
	GameMode->Update->DistributedUpdate(Type::Killer,Type::Explorer);

}
