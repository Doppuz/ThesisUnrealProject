// Fill out your copyright notice in the Description page of Project Settings.


#include "AIBull.h"
#include "Components/BoxComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/GameplayStatics.h"
#include "../Character/CharacterPawnQuad.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AAIBull::AAIBull()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	RootComponent = Collider;

	Collider->SetSimulatePhysics(true);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	PawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("PawnMovement"));
	PawnMovement->MaxSpeed = 300;
	PawnMovement->Acceleration = 1000;

	Collider->OnComponentHit.AddDynamic(this, &AAIBull::OnHit);
	
	CameraArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("ArmComponent"));
	CameraArmComponent->SetupAttachment(RootComponent);
	
	CameraArmComponent->TargetArmLength = 500.f;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(CameraArmComponent);

	Damage = 10.f;
	MaxHealth = 30.f;
	CurrentHealth = MaxHealth; 
}

float AAIBull::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) {
	float DamageTaken = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	CurrentHealth -= DamageTaken;

	UE_LOG(LogTemp,Warning,TEXT("%s: Health Left = %f"), *GetName(), CurrentHealth);

	if(CurrentHealth == 0){
		Destroy();
			/*AGameModeTutorial* GameMode = Cast<AGameModeTutorial>(GetWorld()->GetAuthGameMode());
			switch(ID){
				case 0:
					GameMode->bEnemyDefeated = true;
					break;
				case 1:
					GameMode->CheckPuzzle2(1);
					break;
				case 2:
					GameMode->CheckPuzzle2(2);
					break;
				default:
					break;
			}*/
	}
		
	return DamageTaken;
}

// Called when the game starts or when spawned
void AAIBull::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAIBull::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetActorLocation(FVector(GetActorLocation().X,GetActorLocation().Y,42.f));
}

// Called to bind functionality to input
void AAIBull::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

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

