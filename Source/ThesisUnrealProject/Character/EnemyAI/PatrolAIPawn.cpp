// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrolAIPawn.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SpotLightComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APatrolAIPawn::APatrolAIPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Collider->SetupAttachment(RootComponent);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collider);
	
	CameraArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("ArmComponent"));
	CameraArmComponent->SetupAttachment(Collider);
	
	CameraArmComponent->TargetArmLength = 500.f;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(CameraArmComponent);

	CapsuleTrigger = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger"));
	CapsuleTrigger->SetupAttachment(Collider);

	FirstTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("FirstTrigger"));
	FirstTrigger->SetupAttachment(RootComponent);

	FirstTrigger->SetWorldScale3D(FVector(1.f,4.f,4.f));

	SecondTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("SecondTrigger"));
	SecondTrigger->SetupAttachment(RootComponent);
	
	SecondTrigger->SetWorldScale3D(FVector(1.f,4.f,4.f));

	CapsuleTrigger->SetWorldLocation(FVector(188.f,0.f,0.f));
	CapsuleTrigger->SetWorldRotation(FRotator(0.f,0.f,90.f));
	CapsuleTrigger->SetCapsuleHalfHeight(165.f);
	CapsuleTrigger->SetCapsuleRadius(76.f);
	
	SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));
	SpotLight->SetupAttachment(Collider);

	SpotLight->SetWorldLocation(FVector(24.f,0.f,30.f));
	SpotLight->SetWorldRotation(FRotator(0.f,0.f,-43.f));
	SpotLight->SetIntensity(100000.f);
	SpotLight->SetAttenuationRadius(366.f);
	SpotLight->SetInnerConeAngle(33.f);
	SpotLight->SetOuterConeAngle(37.f);

	Speed = 0.f;

}

// Called when the game starts or when spawned
void APatrolAIPawn::BeginPlay()
{
	Super::BeginPlay();

	CapsuleTrigger->OnComponentBeginOverlap.AddDynamic(this,&APatrolAIPawn::OnOverlap);
	FirstTrigger->OnComponentBeginOverlap.AddDynamic(this,&APatrolAIPawn::OnOverlapTrigger);
	SecondTrigger->OnComponentBeginOverlap.AddDynamic(this,&APatrolAIPawn::OnOverlapTrigger);

	GetWorld()->GetTimerManager().SetTimer(TimerStop, this, &APatrolAIPawn::StopMovement, 2.f, false);
}

// Called every frame
void APatrolAIPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Collider->AddLocalOffset(FVector(Speed,0.f,0.f));

}

// Called to bind functionality to input
void APatrolAIPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APatrolAIPawn::StopMovement() {
	CurrentSpeed = Speed;
	Speed = 0;
	float TimeInterval = FMath::RandRange(1.f, 2.f);
	if(GetWorld() != nullptr)
		GetWorld()->GetTimerManager().SetTimer(TimerStop, this, &APatrolAIPawn::StartMovement, TimeInterval, false);
}

void APatrolAIPawn::StartMovement() {
	Speed = CurrentSpeed;
	float TimeInterval = FMath::RandRange(5.f, 10.f);
	if (GetWorld() != nullptr)
		GetWorld()->GetTimerManager().SetTimer(TimerStop, this, &APatrolAIPawn::StopMovement, TimeInterval, false);
}

#pragma region OnComponentEvent

void APatrolAIPawn::OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit) {

	if (OtherActor->IsA(APawn::StaticClass())){
		APawn* MyPawn = Cast<APawn>(OtherActor);
		AController* MyController = MyPawn->GetController();
		if(MyController != nullptr && MyController->IsA(APlayerController::StaticClass()))
			UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
	}
		
}

void APatrolAIPawn::OnOverlapTrigger(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit) {
	if(OtherActor->IsA(APatrolAIPawn::StaticClass()) && OtherComponent->IsA(UBoxComponent::StaticClass()))
		Collider->AddLocalRotation(FRotator(0.f,180.f,0.f));
}

#pragma endregion OnComponentEvent