// Fill out your copyright notice in the Description page of Project Settings.


#include "Checkpoint.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGameData.h"
#include "../GameModeTutorial.h"
#include "../Character/CharacterPawnQuad.h"
 #include "Components/ProgressBar.h"
#include "Components/WidgetComponent.h"
#include "../UI/UIWidgetDialog.h"
#include "../UI/Elements/HealthBar.h"
#include "../Character/CharacterPawnQuad.h"

// Sets default values
ACheckpoint::ACheckpoint(){
	
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

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

void ACheckpoint::OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit) {
	
	if(OtherActor->IsA(ACharacterPawnQuad::StaticClass())){
			
			if (USaveGameData* SaveGameInstance = Cast<USaveGameData>(UGameplayStatics::CreateSaveGameObject(USaveGameData::StaticClass()))){

				Mesh->SetMaterial(0,EmissiveMaterial);

				UE_LOG(LogTemp,Warning,TEXT("Data Saved"));

				/*if(LevelToUnload != "None"){
					FLatentActionInfo LatentInfo;	
					UGameplayStatics::UnloadStreamLevel(this, LevelToUnload, LatentInfo, true);
					
					AGameModeTutorial* GameMode = Cast<AGameModeTutorial>(GetWorld()->GetAuthGameMode());
					if(GameMode != nullptr)
						GameMode->Levels.Remove(LevelToUnload);

				}*/

				AGameModeTutorial* GameMode = Cast<AGameModeTutorial>(GetWorld()->GetAuthGameMode());

				if(GameMode != nullptr){

					// Set data on the savegame object.
					FVector Location = OtherActor->GetActorLocation() + FVector(0.f,0.f,100.f);
					SaveGameInstance->PlayerLocation = Location;

					SaveGameInstance->Achiever = GameMode->Update->GetBartleTypes()[Achiever];
					SaveGameInstance->Killer = GameMode->Update->GetBartleTypes()[Killer];
					SaveGameInstance->Explorer = GameMode->Update->GetBartleTypes()[Explorer];
					SaveGameInstance->Socializer = GameMode->Update->GetBartleTypes()[Socializer];

					SaveGameInstance->AchieverQ = GameMode->Update->TypesQuestionary[Achiever];
					SaveGameInstance->KillerQ = GameMode->Update->TypesQuestionary[Killer];
					SaveGameInstance->ExplorerQ = GameMode->Update->TypesQuestionary[Explorer];
					SaveGameInstance->SocializerQ = GameMode->Update->TypesQuestionary[Socializer];
					
					SaveGameInstance->Levels = GameMode->Levels;

					SaveGameInstance->AttackSpeed = Cast<ACharacterPawnQuad>(OtherActor)->ProjectileTimeout;
					SaveGameInstance->Hat = Cast<ACharacterPawnQuad>(OtherActor)->EquipmentMesh->GetStaticMesh();

					// Start async save process.
					UGameplayStatics::AsyncSaveGameToSlot(SaveGameInstance, "Checkpoint", 0);

					Cast<ACharacterPawnQuad>(OtherActor)->CurrentHealth = Cast<ACharacterPawnQuad>(OtherActor)->MaxHealth;
					
					UUIWidgetDialog* DialogWidget = Cast<UUIWidgetDialog>(GameMode->GetCurrentWidgetUI());
					if(DialogWidget != nullptr)
						DialogWidget->HealthBar->SetPercent(1.f);

					Trigger->SetCollisionProfileName("NoCollision");

				}

			}

	}

}

