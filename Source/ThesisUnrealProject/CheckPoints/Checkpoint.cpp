// Fill out your copyright notice in the Description page of Project Settings.


#include "Checkpoint.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGameData.h"

// Sets default values
ACheckpoint::ACheckpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Trigger->SetupAttachment(RootComponent);

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

				UE_LOG(LogTemp,Warning,TEXT("Data Saved"));

				// Set data on the savegame object.
				SaveGameInstance->PlayerLocation = MyPawn->GetActorLocation();

				// Start async save process.
				UGameplayStatics::AsyncSaveGameToSlot(SaveGameInstance, "Checkpoint", 0);
			}

		}
	}

}

