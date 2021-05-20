// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnAllyNPC.h"
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
#include "PawnAllyNPC.h"
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

// Sets default values
APawnAllyNPC::APawnAllyNPC(){
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	RootComponent = Collider;

	Collider->SetSimulatePhysics(true);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

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

	ProjectileTimeout = 0.5f;
	MaxHealth = 30;
	InteractiveActor = nullptr;
	MaxRange = 300.f;
}


// Called when the game starts or when spawned
void APawnAllyNPC::BeginPlay(){
	Super::BeginPlay();

	Health = MaxHealth;
}

// Called every frame
void APawnAllyNPC::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);

	FVector NewPos = (GetActorLocation() - PlayerPawn->GetActorLocation());
	NewPos.Z = 0;
    NewPos.Normalize();

    //SetActorRotation(FMath::RInterpTo(GetActorRotation(),NewPos.Rotation(),DeltaTime * 100,0.4));

}

//It equips the object.
void APawnAllyNPC::Equipment() {
	ACharacterPawnQuad* PlayerPawn = Cast<ACharacterPawnQuad>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
	PlayerPawn->EquipmentMesh->SetStaticMesh(MeshToEquip);
}

//Methods called after question onclick event.
void APawnAllyNPC::Choice(int Answer) {
	
	ACharacterPawnQuad* PlayerPawn = Cast<ACharacterPawnQuad>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
	PlayerPawn->SetMousePointer(false);
	APlayerController* PlayerController = Cast<APlayerController>(PlayerPawn->GetController());
	PlayerController->SetInputMode(FInputModeGameOnly());

	switch(Answer){
		case 0:
			Equipment();
			SpeechContator += 1;
			Speak();
			SpeechContator += 1;
			break;
		case 1:
			SpeechContator += 2;
			Speak();
			break;
		default:
			break;
	}
}

//It shows the dialog and change the mode from game to input.
void APawnAllyNPC::StartInteraction() {
	
	Super::StartInteraction();

}

void APawnAllyNPC::EndInteraction() {

	Super::EndInteraction();

	
}

