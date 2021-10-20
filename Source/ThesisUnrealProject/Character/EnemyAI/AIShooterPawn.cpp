// Fill out your copyright notice in the Description page of Project Settings.


#include "AIShooterPawn.h"
#include "AIBull.h"
#include "Components/BoxComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/GameplayStatics.h"
#include "../../Character/CharacterPawnQuad.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "AIController.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "Components/WidgetComponent.h"
#include "../../UI/Elements/HealthBar.h"
#include "Components/ProgressBar.h"
#include "../../UI/UIWidgetDialog.h"
#include "../../Projectile/SquaredProjectile.h"
#include "../../Elements/GeneralElements/CoinController.h"
#include "../../GameModeAbstract.h"


AAIShooterPawn::AAIShooterPawn() {
    
    PrimaryActorTick.bCanEverTick = false;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	RootComponent = Collider;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collider);

	PawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("PawnMovement"));
	PawnMovement->MaxSpeed = 300;
	PawnMovement->Acceleration = 1000;
	
	CameraArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("ArmComponent"));
	CameraArmComponent->SetupAttachment(RootComponent);
	
	CameraArmComponent->TargetArmLength = 500.f;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(CameraArmComponent);

    ProjectileSpawnPosition = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPosition"));
	ProjectileSpawnPosition->SetupAttachment(RootComponent);

	ProjectileSpawnPosition->SetRelativeLocation(FVector(60.f,0,0));

	HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Health Widget"));
	HealthWidgetComponent->SetupAttachment(RootComponent);

	Damage = 10.f;
	MaxHealth = 30.f;
	CurrentHealth = MaxHealth; 

}

float AAIShooterPawn::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) {
    
    float DamageTaken = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	CurrentHealth -= DamageTaken;

	//Update player's UI healthBar		
	UHealthBar* HealthWidget =  Cast<UHealthBar>(HealthWidgetComponent->GetWidget());

	if(HealthWidget != nullptr)
		HealthWidget->HealthBar->SetPercent(CurrentHealth / MaxHealth);

	if(CurrentHealth == 0){
		
		bIAmDestroyed = true;
		End.Broadcast(this);
		
		if(bSpawnCoin)
			GetWorld()->SpawnActor<ACoinController>(SpawnCoin, GetActorLocation(), FRotator::ZeroRotator);

		if(!bNoIncrease){

			AGameModeAbstract* GameMode = Cast<AGameModeAbstract>(GetWorld()->GetAuthGameMode());
			GameMode->IncreaseEnemies();

			UE_LOG(LogTemp,Warning,TEXT("Enemies: %i"), GameMode->GetEnemies());
		
		}

		Destroy();
	}
		
	return DamageTaken;

}

void AAIShooterPawn::BeginPlay() {

    Super::BeginPlay();

	//Need to to this here because when I spawn an actor the GetPawn() is nullptr
	/*Cast<AAIController>(GetController())->GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"),FVector(GetActorLocation().X,
                                                                                 GetActorLocation().Y,
                                                                                 42.f));*/

	//SetBarHealt
	UHealthBar* HealthWidget =  Cast<UHealthBar>(HealthWidgetComponent->GetWidget());

	if(HealthWidget != nullptr)
		HealthWidget->HealthBar->SetPercent(1.f);
	
    
}

void AAIShooterPawn::Shoot() {
    
    ASquaredProjectile* Projectile = GetWorld()->SpawnActor<ASquaredProjectile>(ProjectileClass,ProjectileSpawnPosition->GetComponentLocation(),ProjectileSpawnPosition->GetComponentRotation());
			
	if(Projectile != nullptr)
		Projectile->MyOwner = this;

}
