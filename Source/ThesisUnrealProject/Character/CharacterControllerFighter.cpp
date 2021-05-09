// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterControllerFighter.h"
#include "Components/CapsuleComponent.h"
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
#include "../Animation/MyAnimInstance.h"

// Sets default values
ACharacterControllerFighter::ACharacterControllerFighter(){
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	GetCharacterMovement()->AirControl = 0.2f;

	CameraArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("ArmComponent"));
	CameraArmComponent->SetupAttachment(RootComponent);
	
	CameraArmComponent->bUsePawnControlRotation = true;
	CameraArmComponent->TargetArmLength = 500.f;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(CameraArmComponent);

	CameraComponent->bUsePawnControlRotation = false;

	AttackPose = false;
}


// Called when the game starts or when spawned
void ACharacterControllerFighter::BeginPlay(){
	Super::BeginPlay();

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this,&ACharacterControllerFighter::OnOverlap);
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &ACharacterControllerFighter::OnHit);

	Anim = Cast<UMyAnimInstance>(GetMesh()->GetAnimInstance());
	
}

// Called every frame
void ACharacterControllerFighter::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACharacterControllerFighter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent){
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn",this,&APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp",this,&APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump",IE_Pressed,this,&ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump",IE_Released,this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Shoot",IE_Pressed,this, &ACharacterControllerFighter::ChangeAttack);
	PlayerInputComponent->BindAction("Aim",IE_Pressed,this, &ACharacterControllerFighter::ChangeAttack);

	PlayerInputComponent->BindAxis("MoveForward",this,&ACharacterControllerFighter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this,&ACharacterControllerFighter::MoveRight);
}

void ACharacterControllerFighter::MoveForward(float Axis) {
	/*FRotator Rotation = Controller->GetControlRotation();
	FRotator YawRotation(0.f,Rotation.Yaw,0.f);

	FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);*/

	AddMovementInput(GetActorForwardVector() * Axis);
}

void ACharacterControllerFighter::MoveRight(float Axis) {
	/*FRotator Rotation = Controller->GetControlRotation();
	FRotator YawRotation(0.f,Rotation.Yaw,0.f);

	FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);*/

	AddMovementInput(GetActorRightVector() * Axis);
}

void ACharacterControllerFighter::Shoot() {
	//Gun->PullTrigger();
}


void ACharacterControllerFighter::ChangeAttack() {
	//if(!GetWorld()->GetTimerManager().TimerExists(AttackTimer)){
		//Anim->SetAttack();	
	    PlayAnimMontage(Montage,1, NAME_None);
		
		//GetWorld()->GetTimerManager().SetTimer(AttackTimer,Anim,&UMyAnimInstance::SetAttack,0.85f,false);
	//}
}

void ACharacterControllerFighter::OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit) {
	//Collision with the coins.
	if(OtherActor->IsA(ACoinController::StaticClass())){
	
		ACustomGameMode* MyGameMode = Cast<ACustomGameMode>(GetWorld()->GetAuthGameMode());
		MyGameMode->IncreaseCoins();
		OtherActor->Destroy();
		UUIWidget* UI = Cast<UUIWidget>(MyGameMode->GetCurrentWidgetUI());
		UI->SetCoinsText(MyGameMode->GetCoins());
	
	//Collision with a Cell.
	}else if(OtherActor->IsA(AMazeCell::StaticClass())){

		ACustomGameMode* MyGameMode = Cast<ACustomGameMode>(GetWorld()->GetAuthGameMode());
		AMazeCell* MazeActor = Cast<AMazeCell>(OtherActor);
		MyGameMode->MazeGraph->MoveCurrentNode(MazeActor);
		
		//Increase the percentage of the map if it is the first time I visited the cell.
		if(MazeActor->bIsVisited != true){
			MazeActor->bIsVisited = true;
			MyGameMode->IncreasePercentage();
			UUIWidget* UI = Cast<UUIWidget>(MyGameMode->GetCurrentWidgetUI());
			UI->SetMapText(MyGameMode->GetPercentage());
		}	

		MyGameMode->Populate->DynamicDepthVisit(MyGameMode->MazeGraph->GetCurrentNode());
	
	}

}

void ACharacterControllerFighter::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {
	if(OtherActor->IsA(ACrateElements::StaticClass()) && OtherComponent->IsA(UDestructibleComponent::StaticClass())){
		//UGameplayStatics::ApplyDamage(OtherActor,10,this->GetController(),this,UDamageType::StaticClass());
		UDestructibleComponent* DC = Cast<UDestructibleComponent>(OtherComponent);
		ACrateElements* Actor = Cast<ACrateElements>(OtherActor);
		
		if(!Actor->IAmDestructed)
			DC->ApplyRadiusDamage(100.f,Hit.ImpactPoint, 10.f,30000.f,true);
	}
}


