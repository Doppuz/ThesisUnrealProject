// Fill out your copyright notice in the Description page of Project Settings.


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
#include "../../GameModeAbstract.h"
#include "../../UI/UIWidgetDialog.h"
#include "../../Elements/GeneralElements/CoinController.h"

// Sets default values
AAIBull::AAIBull(){
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	RootComponent = Collider;//->SetupAttachment(RootComponent);

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

	HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Health Widget"));
	HealthWidgetComponent->SetupAttachment(RootComponent);

	Damage = 10.f;
	MaxHealth = 30.f;
	CurrentHealth = MaxHealth; 
}

float AAIBull::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) {
	float DamageTaken = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	CurrentHealth -= DamageTaken;

	//Update player's UI healthBar		
	UHealthBar* HealthWidget =  Cast<UHealthBar>(HealthWidgetComponent->GetWidget());

	if(HealthWidget != nullptr)
		HealthWidget->HealthBar->SetPercent(CurrentHealth / MaxHealth);

	if(CurrentHealth == 0){

		bIAmDestroyed = true;
		End.Broadcast(this);
		
		if(bSpawnCoin) {

			FTransform Transform;
			Transform.SetLocation(GetActorLocation());
			ACoinController* Coin = GetWorld()->SpawnActor<ACoinController>(SpawnCoin, Transform);

		}

		if(!bNoIncrease){
		
			AGameModeAbstract* GameMode = Cast<AGameModeAbstract>(GetWorld()->GetAuthGameMode());
			
			if(!bSpawnCoin){

				GameMode->IncreaseEnemies();
				UE_LOG(LogTemp,Warning,TEXT("Enemies: %i"), GameMode->GetEnemies());

			}

		}
		
		Destroy();

	}
		
	return DamageTaken;
}

// Called when the game starts or when spawned
void AAIBull::BeginPlay()
{
	Super::BeginPlay();

	//Need to to this here because when I spawn an actor the GetPawn() is nullptr
	Cast<AAIController>(GetController())->GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"),FVector(GetActorLocation().X,
                                                                                 GetActorLocation().Y,
                                                                                 42.f));

	//SetBarHealt
	UHealthBar* HealthWidget =  Cast<UHealthBar>(HealthWidgetComponent->GetWidget());

	if(HealthWidget != nullptr)
		HealthWidget->HealthBar->SetPercent(1.f);
	
	Collider->OnComponentHit.AddDynamic(this, &AAIBull::OnHit);
	Mesh->OnComponentHit.AddDynamic(this, &AAIBull::OnHit);

}

void AAIBull::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {

	//If I hit the player, I make him damage.
	if(OtherActor->IsA(ACharacterPawnQuad::StaticClass())){
		ACharacterPawnQuad* PlayerPawn = Cast<ACharacterPawnQuad>(OtherActor);
		if(PlayerPawn->GetController()->IsA(APlayerController::StaticClass())){
			FPointDamageEvent DamageEvent(Damage,Hit,this->GetVelocity(),nullptr);
			OtherActor->TakeDamage(Damage,DamageEvent,PlayerPawn->GetController(),this);
		}
	}

}

