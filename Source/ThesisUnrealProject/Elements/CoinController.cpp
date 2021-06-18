// Fill out your copyright notice in the Description page of Project Settings.


#include "CoinController.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "../GameModeTutorial.h"
#include "../UI/UIWidgetDialog.h"
#include "Components/TextBlock.h"

// Sets default values
ACoinController::ACoinController(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	CoinCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Coin Collider"));
	CoinCollider->SetupAttachment(RootComponent);

	CoinMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Coin Mesh"));
	CoinMesh->SetupAttachment(CoinCollider);

	Triggers = CreateDefaultSubobject<USceneComponent>(TEXT("Triggers"));
	Triggers->SetupAttachment(RootComponent);
	
	TopBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TopBox"));
	TopBox->SetupAttachment(Triggers);

	BotBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BotBox"));
	BotBox->SetupAttachment(Triggers);
	
	RotationValue = 2.f;
	OffSetValue = 1.f;
	ID = -1;
	bIsCollected = false;
}

// Called when the game starts or when spawned
void ACoinController::BeginPlay(){
	Super::BeginPlay();
	
	TopBox->OnComponentBeginOverlap.AddDynamic(this, &ACoinController::OnBoxOverlap);
	BotBox->OnComponentBeginOverlap.AddDynamic(this, &ACoinController::OnBoxOverlap);
	CoinCollider->OnComponentBeginOverlap.AddDynamic(this, &ACoinController::OnCoinOverlap);
}

// Called every frame
void ACoinController::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

	FQuat Quaternion = FQuat(FRotator(0,RotationValue,0));

	AddActorLocalRotation(Quaternion);

	CoinCollider->AddLocalOffset(FVector(0,0,OffSetValue));
	
}

void ACoinController::OnBoxOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent,
 int otherBodyIndex, bool fromsweep, const FHitResult & Hit) {

	OffSetValue = -OffSetValue;

}

void ACoinController::OnCoinOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit) {
	
	if(OtherActor->IsA(APawn::StaticClass())){
		AGameModeTutorial* GameMode = Cast<AGameModeTutorial>(GetWorld()->GetAuthGameMode());
		GameMode->IncreaseCoins();
		bIsCollected = true;
		CollectedDelegate.Broadcast();
		UUIWidgetDialog* UI = Cast<UUIWidgetDialog>(GameMode->GetCurrentWidgetUI());
		if(UI->CoinText->GetVisibility() == ESlateVisibility::Hidden)
			UI->CoinText->SetVisibility(ESlateVisibility::Visible);
		UI->SetCoinText(GameMode->GetCoins());
		Destroy();
	}
}

