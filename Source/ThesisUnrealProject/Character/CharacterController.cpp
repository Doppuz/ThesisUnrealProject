// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterController.h"
#include "Components/CapsuleComponent.h"
#include "../Elements/CoinController.h"
#include "../CustomGameMode.h"
#include "Blueprint/UserWidget.h"

// Sets default values
ACharacterController::ACharacterController(){
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	GetCharacterMovement()->AirControl = 0.2f;

	CameraArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("ArmComponent"));
	CameraArmComponent->SetupAttachment(RootComponent);
	CameraArmComponent->TargetArmLength = 500.f;
	CameraArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(CameraArmComponent,USpringArmComponent::SocketName);

	CameraComponent->bUsePawnControlRotation = false;
}

void ACharacterController::MoveForward(float Axis) {
	
	FRotator Rotation = Controller->GetControlRotation();
	FRotator YawRotation(0.f,Rotation.Yaw,0.f);

	FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	AddMovementInput(Direction,Axis);

}

void ACharacterController::MoveRight(float Axis) {
	FRotator Rotation = Controller->GetControlRotation();
	FRotator YawRotation(0.f,Rotation.Yaw,0.f);

	FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(Direction,Axis);
}

// Called when the game starts or when spawned
void ACharacterController::BeginPlay(){
	Super::BeginPlay();
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this,&ACharacterController::OnOverlap);
}

// Called every frame
void ACharacterController::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacterController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent){
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn",this,&APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp",this,&APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump",IE_Pressed,this,&ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump",IE_Released,this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward",this,&ACharacterController::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this,&ACharacterController::MoveRight);
}

void ACharacterController::OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit) {
	if(OtherActor->IsA(ACoinController::StaticClass())){
		ACustomGameMode* MyGameMode = Cast<ACustomGameMode>(GetWorld()->GetAuthGameMode());
		MyGameMode->IncreaseCoins();
		OtherActor->Destroy();
		UE_LOG(LogTemp,Warning,TEXT("%d"),MyGameMode->GetCoins());
		UUserWidget* UI = MyGameMode->GetCurrentWidgetUI();
		UI->GetRootWidget()->GetC
	}

}

