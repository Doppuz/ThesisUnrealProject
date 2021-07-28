// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC1DoorSpawnAlly.h"
#include "../Elements/Door.h"
#include "../Character/PawnInteractiveClass.h"
#include "Components/BoxComponent.h"
#include "../Character/CharacterPawnQuad.h"
#include "Kismet/GameplayStatics.h"
#include "../Character/AICharacterPawnQuad.h"
#include "../GameModeTutorial.h"

// Sets default values
ANPC1DoorSpawnAlly::ANPC1DoorSpawnAlly()
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

	NPCs = CreateDefaultSubobject<USceneComponent>(TEXT("NPCs"));
	NPCs->SetupAttachment(RootComponent);

	NPC1 = CreateDefaultSubobject<UChildActorComponent>(TEXT("NPC1"));
	NPC1->SetupAttachment(NPCs);

	Triggers = CreateDefaultSubobject<USceneComponent>(TEXT("Triggers"));
	Triggers->SetupAttachment(RootComponent);

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Trigger->SetupAttachment(Triggers);

	Trigger->OnComponentBeginOverlap.AddDynamic(this,&ANPC1DoorSpawnAlly::OnOverlap);

	bLeftChoice = false;
	bRightChoice = false;

}

// Called when the game starts or when spawned
void ANPC1DoorSpawnAlly::BeginPlay()
{
	Super::BeginPlay();

//---- Need to pass the parameter to the mesh because they are not exposed -----

	APawnInteractiveClass* NPC = Cast<APawnInteractiveClass>(Cast<UChildActorComponent>(NPC1)->GetChildActor());

	/*if(NPC->Speech.Num() > 0)
		NPC->Speech = Speech;
	
	if(NPC->Speech.Num() > 0)
		NPC->Questions = Questions;
	NPC->QuestionAt = QuestionAt;
	NPC->MeshToEquip = MeshToEquip;*/

	NPC->LeftChoice.AddDynamic(this,&ANPC1DoorSpawnAlly::LeftChoiceEvent);
	NPC->RightChoice.AddDynamic(this,&ANPC1DoorSpawnAlly::RightChoiceEvent);
	NPC->EndDialog.AddDynamic(this,&ANPC1DoorSpawnAlly::EndChoiceEvent);

}

// Called every frame
void ANPC1DoorSpawnAlly::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANPC1DoorSpawnAlly::LeftChoiceEvent() {

	bLeftChoice = true;

	FLatentActionInfo LatentInfo;
	UGameplayStatics::LoadStreamLevel(this, TEXT("SixthChoice"), true, false, LatentInfo);
	
	AGameModeTutorial* GameMode = Cast<AGameModeTutorial>(GetWorld()->GetAuthGameMode());
	
	if(!GameMode->Levels.Contains("SixthChoice"))
		GameMode->Levels.Add("SixthChoice");

	//Update Bartle's values
	/*UBartleManagerGameInstance* Bartle = Cast<UBartleManagerGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	Bartle->DistributedUpdate(Type::Socializer,Type::Killer);*/
	
	ACharacterPawnQuad* PlayerPawn = Cast<ACharacterPawnQuad>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));

	APawnInteractiveClass* NPC = Cast<APawnInteractiveClass>(Cast<UChildActorComponent>(NPC1)->GetChildActor());

	NPC->SpeechContator += 1;
	NPC->Speak();
	NPC->SpeechContator = NPC->Speech.Num() - 1;
	NPC->Speak();
}

void ANPC1DoorSpawnAlly::RightChoiceEvent() {
	
	bRightChoice = true;
	
	FLatentActionInfo LatentInfo;
	UGameplayStatics::LoadStreamLevel(this, TEXT("SixthChoice"), true, false, LatentInfo);

	AGameModeTutorial* GameMode = Cast<AGameModeTutorial>(GetWorld()->GetAuthGameMode());
	GameMode->Levels.Add("SixthChoice");

	//Update Bartle's values
	/*UBartleManagerGameInstance* Bartle = Cast<UBartleManagerGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	Bartle->DistributedUpdate(Type::Killer,Type::Socializer);*/
	
	Trigger->SetCollisionProfileName("NoCollision");

	ACharacterPawnQuad* PlayerPawn = Cast<ACharacterPawnQuad>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));

	APawnInteractiveClass* NPC = Cast<APawnInteractiveClass>(Cast<UChildActorComponent>(NPC1)->GetChildActor());
	NPC->SpeechContator += 1;
	NPC->Speak();
}

void ANPC1DoorSpawnAlly::EndChoiceEvent(APawnInteractiveClass* SpokenActor) {
	ADoor* Door = Cast<ADoor>(Cast<UChildActorComponent>(Door1)->GetChildActor());
	Door->bOpenDoor = true;
}

void ANPC1DoorSpawnAlly::OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit) {
	
	if(OtherActor->IsA(ACharacterPawnQuad::StaticClass())){
		APawn* MyPawn = Cast<APawn>(OtherActor);
		if(MyPawn->GetController()->IsA(APlayerController::StaticClass())){
			GetWorld()->SpawnActor<AAICharacterPawnQuad>(AllyClass,
				FVector(Trigger->GetComponentLocation().X,Trigger->GetComponentLocation().Y,MyPawn->GetActorLocation().Z)
				,GetActorRotation());
			Destroy();
		}
	}

}
