// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterPawnQuad.h"
#include "Components/BoxComponent.h"
#include "../Elements/CoinController.h"
#include "../Elements/CrateElements.h"
#include "../CustomGameMode.h"
#include "Blueprint/UserWidget.h"
#include "../UI/UIWidget.h"
#include "../GameManager/MazeCell.h"
#include "Kismet/GameplayStatics.h"
#include "DestructibleComponent.h"
#include "../GameManager/MazegenerationPopulate.h"
#include "../Gun/GunController.h"

// Sets default values
ACharacterPawnQuad::ACharacterPawnQuad(){
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	RootComponent = Collider;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	CameraArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("ArmComponent"));
	CameraArmComponent->SetupAttachment(RootComponent);
	
	CameraArmComponent->bUsePawnControlRotation = true;
	CameraArmComponent->TargetArmLength = 500.f;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(CameraArmComponent);

	CameraComponent->bUsePawnControlRotation = true;

	MovementSpeed = 100.f;

}


// Called when the game starts or when spawned
void ACharacterPawnQuad::BeginPlay(){
	Super::BeginPlay();

	//GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this,&ACharacterControllerQuad::OnOverlap);
	//GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &ACharacterControllerQuad::OnHit);
}

// Called every frame
void ACharacterPawnQuad::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

	if(!VectorMovement.IsZero()){
		FVector NewLocation = GetActorLocation() + (VectorMovement * DeltaTime * MovementSpeed);
		SetActorLocation(NewLocation);
	}
}

// Called to bind functionality to input
void ACharacterPawnQuad::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent){
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn",this,&APawn::AddControllerYawInput);
	//PlayerInputComponent->BindAxis("LookUp",this,&APawn::AddControllerPitchInput);

	//PlayerInputComponent->BindAction("Jump",IE_Pressed,this,&ACharacter::Jump);
	//PlayerInputComponent->BindAction("Jump",IE_Released,this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Shoot",IE_Pressed,this, &ACharacterPawnQuad::Shoot);

	PlayerInputComponent->BindAxis("MoveForward",this,&ACharacterPawnQuad::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this,&ACharacterPawnQuad::MoveRight);
}

void ACharacterPawnQuad::MoveForward(float Axis) {
	/*FRotator Rotation = Controller->GetControlRotation();
	FRotator YawRotation(0.f,Rotation.Yaw,0.f);

	FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);*/

	VectorMovement.X = FMath::Clamp(Axis,-1.f,+1.f);
}

void ACharacterPawnQuad::MoveRight(float Axis) {
	/*FRotator Rotation = Controller->GetControlRotation();
	FRotator YawRotation(0.f,Rotation.Yaw,0.f);

	FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);*/

	VectorMovement.Y = FMath::Clamp(Axis,-1.f,+1.f);
}

void ACharacterPawnQuad::Shoot() {

}

void ACharacterPawnQuad::OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit) {


}

void ACharacterPawnQuad::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {

}

