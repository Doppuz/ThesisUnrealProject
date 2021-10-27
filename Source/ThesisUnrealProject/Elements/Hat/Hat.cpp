// Fill out your copyright notice in the Description page of Project Settings.


#include "Hat.h"
#include "../../Character/CharacterPawnQuad.h"
#include "../../GameModeAbstract.h"

// Sets default values
AHat::AHat(){

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AHat::BeginPlay(){

	Super::BeginPlay();

	Mesh->OnComponentBeginOverlap.AddDynamic(this,&AHat::OnHatOverlap);

	AGameModeAbstract* GameMode = Cast<AGameModeAbstract>(GetWorld()->GetAuthGameMode());
	GameMode->TotalCoins += 1;
	
}

void AHat::OnHatOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit) {
	
	if(OtherActor->IsA(ACharacterPawnQuad::StaticClass())){

		Cast<ACharacterPawnQuad>(OtherActor)->EquipmentMesh->SetStaticMesh(Mesh->GetStaticMesh());
		Cast<ACharacterPawnQuad>(OtherActor)->HatMaterials.Add(Mesh->GetMaterials());
		Cast<ACharacterPawnQuad>(OtherActor)->ChangeHat();
		Cast<ACharacterPawnQuad>(OtherActor)->HatsOwned.Add(HatID);

		AGameModeAbstract* GameMode = Cast<AGameModeAbstract>(GetWorld()->GetAuthGameMode());
		GameMode->IncreaseCoins();
		UE_LOG(LogTemp,Warning,TEXT("Coins: %i"), GameMode->GetCoins());

		Destroy();

	}

}

// Called every frame
void AHat::Tick(float DeltaTime){

	Super::Tick(DeltaTime);

	AddActorWorldRotation(FRotator(0.f,3.f,0.f));

}

