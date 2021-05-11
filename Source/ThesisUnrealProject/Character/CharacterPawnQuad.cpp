// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterPawnQuad.h"
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

// Sets default values
ACharacterPawnQuad::ACharacterPawnQuad(){
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	RootComponent = Collider;

	Collider->SetSimulatePhysics(true);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	ProjectileSpawnPosition = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPosition"));
	ProjectileSpawnPosition->SetupAttachment(RootComponent);

	ProjectileSpawnPosition->SetRelativeLocation(FVector(60.f,0,0));

	/*CameraArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("ArmComponent"));
	CameraArmComponent->SetupAttachment(RootComponent);
	
	CameraArmComponent->bUsePawnControlRotation = true;
	CameraArmComponent->TargetArmLength = 500.f;*/

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(RootComponent);

	CameraComponent->SetRelativeLocation(FVector(703.433655,0.000244,762.538635));
	CameraComponent->SetRelativeRotation(FRotator(0,-48,0));

	MovementSpeed = 400.f;
	RotationSpeed = 400.f;
	JumpForce = 300.f;
	bAmIJump = false;
	bAmIShooting = false;
	ProjectileTimeout = 0.5f;
}


// Called when the game starts or when spawned
void ACharacterPawnQuad::BeginPlay(){
	Super::BeginPlay();

	InitialRotation = CameraComponent->GetComponentRotation();
	//GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this,&ACharacterControllerQuad::OnOverlap);
	//Collider->OnComponentHit.AddDynamic(this, &ACharacterPawnQuad::OnHit);
}

// Called every frame
void ACharacterPawnQuad::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

	if(!VectorMovement.IsZero()){
		FVector NewLocation = GetActorLocation() + (VectorMovement * DeltaTime * MovementSpeed);
		AddActorLocalOffset(VectorMovement);
	}

	if(!Rotation.IsZero()){
		AddActorLocalRotation(Rotation);
	}

	if(!CameraRotation.IsZero()){
		float CurrentPitch = CameraComponent->GetComponentRotation().Pitch;
		//if((CurrentPitch + CameraRotation.Pitch) > InitialRotation.Pitch - 30 && (CurrentPitch + CameraRotation.Pitch) < InitialRotation.Pitch + 30)
		//	CameraComponent->AddLocalRotation(CameraRotation);
	}

}

// Called to bind functionality to input
void ACharacterPawnQuad::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent){
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn",this,&ACharacterPawnQuad::RotateYaw);
	PlayerInputComponent->BindAxis("LookUp",this,&ACharacterPawnQuad::RotatePitch);

	PlayerInputComponent->BindAction("Jump",IE_Pressed,this,&ACharacterPawnQuad::Jump);
	//PlayerInputComponent->BindAction("Jump",IE_Released,this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Shoot",IE_Pressed,this, &ACharacterPawnQuad::Shoot);

	PlayerInputComponent->BindAxis("MoveForward",this,&ACharacterPawnQuad::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this,&ACharacterPawnQuad::MoveRight);
}

void ACharacterPawnQuad::MoveForward(float Axis) {
	/*FRotator Rotation = Controller->GetControlRotation();
	FRotator YawRotation(0.f,Rotation.Yaw,0.f);

	FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);*/

	VectorMovement.X = FMath::Clamp(Axis,-1.f,+1.f) * GetWorld()->DeltaTimeSeconds * MovementSpeed;
}

void ACharacterPawnQuad::MoveRight(float Axis) {
	/*FRotator Rotation = Controller->GetControlRotation();
	FRotator YawRotation(0.f,Rotation.Yaw,0.f);

	FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);*/

	VectorMovement.Y = Axis *  GetWorld()->DeltaTimeSeconds * MovementSpeed;
}

void ACharacterPawnQuad::RotatePitch(float Axis) {
	CameraRotation.Pitch = -Axis *  GetWorld()->DeltaTimeSeconds * RotationSpeed/4;
}

void ACharacterPawnQuad::RotateYaw(float Axis) {
	Rotation.Yaw = Axis *  GetWorld()->DeltaTimeSeconds * RotationSpeed;
}

void ACharacterPawnQuad::Jump() {
	if(!bAmIJump){
		Collider->AddImpulse(GetActorUpVector() * JumpForce,NAME_None,true);
		bAmIJump = true;
		GetWorld()->GetTimerManager().SetTimer(JumpTimer,this,&ACharacterPawnQuad::SetJump,(JumpForce / 5)/100,false);
	}
}

void ACharacterPawnQuad::SetJump(){
	bAmIJump = false;
}

void ACharacterPawnQuad::Shoot() {
	if(!bAmIShooting){
		GetWorld()->SpawnActor<ASquaredProjectile>(ProjectileClass,ProjectileSpawnPosition->GetComponentLocation(),ProjectileSpawnPosition->GetComponentRotation());
		bAmIShooting = true;
		GetWorld()->GetTimerManager().SetTimer(ShotTimer,this, &ACharacterPawnQuad::SetShooting, ProjectileTimeout, false);
	}
}

void ACharacterPawnQuad::SetShooting() {
	bAmIShooting = false;
}

void ACharacterPawnQuad::OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit) {


}

void ACharacterPawnQuad::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {
	
}

