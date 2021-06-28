// Fill out your copyright notice in the Description page of Project Settings.


#include "Checkpoint.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGameData.h"
#include "../GameModeTutorial.h"
#include "../Character/CharacterPawnQuad.h"

// Sets default values
ACheckpoint::ACheckpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Trigger->SetupAttachment(RootComponent);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();
	
	Trigger->OnComponentBeginOverlap.AddDynamic(this,&ACheckpoint::OnOverlap);
}

// Called every frame
void ACheckpoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACheckpoint::OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit) {
	
	if(OtherActor->IsA(APawn::StaticClass())){
		APawn* MyPawn = Cast<APawn>(OtherActor);
		if(MyPawn->GetController()->IsA(APlayerController::StaticClass())){
			
			if (USaveGameData* SaveGameInstance = Cast<USaveGameData>(UGameplayStatics::CreateSaveGameObject(USaveGameData::StaticClass()))){

				Mesh->SetMaterial(0,EmissiveMaterial);

				UE_LOG(LogTemp,Warning,TEXT("Data Saved"));

				if(LevelToUnload != ""){
					FLatentActionInfo LatentInfo;	
					UGameplayStatics::UnloadStreamLevel(this, LevelToUnload, LatentInfo, true);
					
					AGameModeTutorial* GameMode = Cast<AGameModeTutorial>(GetWorld()->GetAuthGameMode());
					GameMode->Levels.Remove(LevelToUnload);

				}

				AGameModeTutorial* GameMode = Cast<AGameModeTutorial>(GetWorld()->GetAuthGameMode());

				// Set data on the savegame object.
				SaveGameInstance->PlayerLocation = MyPawn->GetActorLocation();
				
				SaveGameInstance->Achiever = GameMode->GetBartleTypes()[Achiever];
				SaveGameInstance->Killer = GameMode->GetBartleTypes()[Killer];
				SaveGameInstance->Explorer = GameMode->GetBartleTypes()[Explorer];
				SaveGameInstance->Socializer = GameMode->GetBartleTypes()[Socializer];
				SaveGameInstance->Levels = GameMode->Levels;

				// Start async save process.
				UGameplayStatics::AsyncSaveGameToSlot(SaveGameInstance, "Checkpoint", 0);

				Cast<ACharacterPawnQuad>(MyPawn)->CurrentHealth = Cast<ACharacterPawnQuad>(MyPawn)->MaxHealth;

				Trigger->SetCollisionProfileName("NoCollision");

			}

		}
	}

}

