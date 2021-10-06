// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrolAI2.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/SpotLightComponent.h"
#include "AIController.h"
#include "Components/CapsuleComponent.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APatrolAI2::APatrolAI2()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	RootComponent = Collider;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collider);
	
	CameraArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("ArmComponent"));
	CameraArmComponent->SetupAttachment(Collider);
	
	CameraArmComponent->TargetArmLength = 500.f;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(CameraArmComponent);

	PawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("PawnMovement"));
	PawnMovement->MaxSpeed = 300;
	PawnMovement->Acceleration = 1000;

	SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));
	SpotLight->SetupAttachment(Collider);

	SpotLight->SetWorldLocation(FVector(24.f,0.f,30.f));
	SpotLight->SetWorldRotation(FRotator(0.f,0.f,-43.f));
	SpotLight->SetIntensity(100000.f);
	SpotLight->SetAttenuationRadius(366.f);
	SpotLight->SetInnerConeAngle(33.f);
	SpotLight->SetOuterConeAngle(37.f);
	
	CapsuleTrigger = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger"));
	CapsuleTrigger->SetupAttachment(Collider);
	CapsuleTrigger->SetWorldLocation(FVector(188.f,0.f,0.f));
	CapsuleTrigger->SetWorldRotation(FRotator(0.f,0.f,90.f));
	CapsuleTrigger->SetCapsuleHalfHeight(165.f);
	CapsuleTrigger->SetCapsuleRadius(76.f);

	StartIndex = 0;
	StartDirection = true;

}

void APatrolAI2::SetInitialValue(FVector Pos, int Contator, bool Direction, bool SameDirection) {
	
	Cast<AAIController>(GetController())->GetBlackboardComponent()->SetValueAsVector("NewPosition",Pos);
	Cast<AAIController>(GetController())->GetBlackboardComponent()->SetValueAsInt("Contator",Contator);
	Cast<AAIController>(GetController())->GetBlackboardComponent()->SetValueAsBool("Direction",Direction);
	Cast<AAIController>(GetController())->GetBlackboardComponent()->SetValueAsBool("SameDirection",SameDirection);

}

// Called when the game starts or when spawned
void APatrolAI2::BeginPlay(){

	Super::BeginPlay();

	InitialPos = GetActorLocation();

	CapsuleTrigger->OnComponentBeginOverlap.AddDynamic(this,&APatrolAI2::OnOverlap);
	
    //Set the initial value of the BTree.
    SetInitialValue(Positions[StartIndex],StartIndex,true, StartDirection);

}

// Called to bind functionality to input
void APatrolAI2::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APatrolAI2::OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit) {

	if (OtherActor->IsA(APawn::StaticClass())){
		APawn* MyPawn = Cast<APawn>(OtherActor);
		AController* MyController = MyPawn->GetController();
		if(MyController != nullptr && MyController->IsA(APlayerController::StaticClass()))
			UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
	}

}

