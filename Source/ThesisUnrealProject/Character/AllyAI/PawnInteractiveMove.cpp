// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnInteractiveMove.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/PrimitiveComponent.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "AIController.h"

// Sets default values
APawnInteractiveMove::APawnInteractiveMove(){
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

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

	SetInitialValue(Positions[0], 0, true, true);
}

void APawnInteractiveMove::SetInitialValue(FVector Pos, int Contator, bool Direction,bool SameDirection) {
	
	Cast<AAIController>(GetController())->GetBlackboardComponent()->SetValueAsVector("NewPosition",Pos);
	Cast<AAIController>(GetController())->GetBlackboardComponent()->SetValueAsVector("StartLocation",Pos);
	Cast<AAIController>(GetController())->GetBlackboardComponent()->SetValueAsInt("Contator",Contator);
	Cast<AAIController>(GetController())->GetBlackboardComponent()->SetValueAsBool("Direction",Direction);
	Cast<AAIController>(GetController())->GetBlackboardComponent()->SetValueAsBool("NotEIsPressed",true);
	Cast<AAIController>(GetController())->GetBlackboardComponent()->SetValueAsBool("SameDirection",SameDirection);
	
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