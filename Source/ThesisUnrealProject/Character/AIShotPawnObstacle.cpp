// Fill out your copyright notice in the Description page of Project Settings.


#include "AIShotPawnObstacle.h"
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
#include "Components/TextBlock.h"
#include "Engine/TriggerVolume.h"
#include "Engine/LatentActionManager.h"
#include "Components/SpotLightComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/WidgetComponent.h"
#include "../UI/HealthBar.h"
#include "Components/ProgressBar.h"

// Sets default values
AAIShotPawnObstacle::AAIShotPawnObstacle(){
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root =  CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Collider->SetupAttachment(RootComponent);

	Collider->SetSimulatePhysics(false);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collider);

	EquipmentMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EquipmentMesh"));
	EquipmentMesh->SetupAttachment(Collider);

	EquipmentMesh->SetWorldLocation(FVector(0,0,32));

	ProjectileSpawnPosition = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPosition"));
	ProjectileSpawnPosition->SetupAttachment(Collider);

	ProjectileSpawnPosition->SetRelativeLocation(FVector(60.f,0,0));

	CameraArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("ArmComponent"));
	CameraArmComponent->SetupAttachment(Collider);
	
	CameraArmComponent->TargetArmLength = 500.f;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(CameraArmComponent);

	TriggerLeft = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerLeft"));
	TriggerLeft->SetupAttachment(RootComponent);

	TriggerRight = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerRight"));
	TriggerRight->SetupAttachment(RootComponent);

	MovementSpeed = 2.f;
	bAmIShooting = false;
	ProjectileTimeout = 0.5f;
	bStationary = true;

}


// Called when the game starts or when spawned
void AAIShotPawnObstacle::BeginPlay(){
	Super::BeginPlay();
	
	TriggerLeft->OnComponentBeginOverlap.AddDynamic(this,&AAIShotPawnObstacle::OnOverlap);
	TriggerRight->OnComponentBeginOverlap.AddDynamic(this,&AAIShotPawnObstacle::OnOverlap);

	Shoot();

}


// Called every frame
void AAIShotPawnObstacle::Tick(float DeltaTime){
	
	Super::Tick(DeltaTime);

	if(!bStationary)
		Collider->AddLocalOffset(GetActorForwardVector()*MovementSpeed);
	else{
		TriggerLeft->SetCollisionProfileName("NoCollision");
		TriggerRight->SetCollisionProfileName("NoCollision");
	}

}

void AAIShotPawnObstacle::Shoot() {
	
	ASquaredProjectile* Projectile = GetWorld()->SpawnActor<ASquaredProjectile>(ProjectileClass,ProjectileSpawnPosition->GetComponentLocation(),ProjectileSpawnPosition->GetComponentRotation());
			
	if(Projectile != nullptr)
		Projectile->MyOwner = this;
			
	GetWorld()->GetTimerManager().SetTimer(ShotTimer,this, &AAIShotPawnObstacle::Shoot, ProjectileTimeout, false);
}


void AAIShotPawnObstacle::OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit) {

	if(OtherActor == this && OtherComponent->IsA(UBoxComponent::StaticClass()))
		MovementSpeed = -MovementSpeed;

}
