// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnInteractiveMove.h"
#include "Components/BoxComponent.h"
#include "../Elements/CoinController.h"
#include "../Elements/CrateElements.h"
#include "Blueprint/UserWidget.h"
#include "../UI/UIWidget.h"
#include "../GameManager/MazeCell.h"
#include "Kismet/GameplayStatics.h"
#include "DestructibleComponent.h"
#include "../GameManager/MazegenerationPopulate.h"
#include "../Projectile/SquaredProjectile.h"
#include "Components/PrimitiveComponent.h"
#include "../AI/QuadAIController.h"
#include "DrawDebugHelpers.h"
#include "PawnInteractiveClass.h"
#include "../GameModeTutorial.h"
#include "../UI/UIWidgetDialog.h"
#include "../UI/UIBox.h"
#include "../UI/UserWidgetList.h"
#include "../Elements/Door.h"
#include "../Character/CharacterPawnQuad.h"
#include "../AI/AllyQuadAIController.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/FloatingPawnMovement.h"

// Sets default values
APawnInteractiveMove::APawnInteractiveMove(){
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EquipmentMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EquipmentMesh"));
	EquipmentMesh->SetupAttachment(RootComponent);

	EquipmentMesh->SetWorldLocation(FVector(0,0,32));

	ProjectileSpawnPosition = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPosition"));
	ProjectileSpawnPosition->SetupAttachment(RootComponent);

	ProjectileSpawnPosition->SetRelativeLocation(FVector(60.f,0,0));

	CameraArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("ArmComponent"));
	CameraArmComponent->SetupAttachment(RootComponent);
	
	CameraArmComponent->TargetArmLength = 500.f;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(CameraArmComponent);

	PawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("PawnMovement"));
	PawnMovement->MaxSpeed = 300;
	PawnMovement->Acceleration = 1000;

	InteractiveActor = nullptr;
}


// Called when the game starts or when spawned
void APawnInteractiveMove::BeginPlay(){
	Super::BeginPlay();

	bFocus = false;
}

// Called every frame
void APawnInteractiveMove::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

}

//Methods called after question onclick event.
void APawnInteractiveMove::Choice(int Answer) {
	
	
}

void APawnInteractiveMove::StartInteraction() {
	
	Cast<AAIController>(GetController())->GetBlackboardComponent()->SetValueAsBool(TEXT("NotEIsPressed"),false);
	Super::StartInteraction();

}

void APawnInteractiveMove::EndInteraction() {
	
	Cast<AAIController>(GetController())->GetBlackboardComponent()->SetValueAsBool(TEXT("NotEIsPressed"),true);
	Super::EndInteraction();
	
}