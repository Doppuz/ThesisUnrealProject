// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterPawnQuad.h"
#include "Components/BoxComponent.h"
#include "Blueprint/UserWidget.h"
#include "../UI/UIWidget.h"
#include "Kismet/GameplayStatics.h"
#include "DestructibleComponent.h"
#include "../Projectile/SquaredProjectile.h"
#include "../AI/QuadAIController.h"
#include "../GameModeAbstract.h"
#include "../UI/UIWidgetDialog.h"
#include "Components/TextBlock.h"
#include "Engine/TriggerVolume.h"
#include "Engine/LatentActionManager.h"
#include "Components/SpotLightComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/WidgetComponent.h"
#include "../UI/HealthBar.h"
#include "Components/ProgressBar.h"
#include "Components/SizeBox.h"
#include "../UI/UIBox.h"

// Sets default values
ACharacterPawnQuad::ACharacterPawnQuad(){
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	RootComponent = Collider;

	Collider->SetSimulatePhysics(true);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	EquipmentMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EquipmentMesh"));
	EquipmentMesh->SetupAttachment(RootComponent);

	EquipmentMesh->SetWorldLocation(FVector(0,0,32));

	ProjectileSpawnPosition = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPosition"));
	ProjectileSpawnPosition->SetupAttachment(RootComponent);

	ProjectileSpawnPosition->SetRelativeLocation(FVector(60.f,0,0));

	CameraArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("ArmComponent"));
	CameraArmComponent->SetupAttachment(RootComponent);
	
	CameraArmComponent->TargetArmLength = 500.f;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(CameraArmComponent);
	
	FollowAllyPosition = CreateDefaultSubobject<USceneComponent>(TEXT("FollowAlly"));
	FollowAllyPosition->SetupAttachment(RootComponent);

	SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLightComponent"));
	SpotLight->SetupAttachment(RootComponent);

	SpotLight->SetWorldLocation(FVector(30.f,0.f,0.f));
	SpotLight->SetWorldRotation(FRotator(-20.f,0.f,0.f));	
	SpotLight->Intensity = 0.f;	

	HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Health Widget"));
	HealthWidgetComponent->SetupAttachment(RootComponent);

	MovementSpeed = 400.f;
	RotationSpeed = 400.f;
	JumpForce = 500.f;
	bAmIJump = false;
	bAmIShooting = false;
	ProjectileTimeout = 0.5f;
	CurrentHealth = 0;
	MaxHealth = 30;
	AllyNPC = nullptr;
	MaxRange = 300.f;
	InteractiveActor = nullptr;
	bStopMovement = false;
	MaxRandomDistance = 300.f;
	bStationary = true;
	NumberOfRepetitions = 0;
	bIsVisible = true;
}


// Called when the game starts or when spawned
void ACharacterPawnQuad::BeginPlay(){
	Super::BeginPlay();

	SpotLight->Intensity = 0.f;	

	CurrentHealth = MaxHealth;

	//SetBarHealt

	SetHealthPercentage(1.f);
	
	InitialRotation = CameraArmComponent->GetComponentRotation();
}

//Add damage. If healt == 0, destroy the actor. Switch case to apply changes to the manager.
float ACharacterPawnQuad::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) {
	
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if(GetController()->IsA(APlayerController::StaticClass())){
		if(!bCharacterInvincible){
			CurrentHealth -= FMath::Min(CurrentHealth,Damage);

			//Update player's UI healthBar		
			AGameModeAbstract* GameMode = Cast<AGameModeAbstract>(GetWorld()->GetAuthGameMode());
			UUIWidgetDialog* DialogWidget = Cast<UUIWidgetDialog>(GameMode->GetCurrentWidgetUI());
			DialogWidget->HealthBar->SetPercent(CurrentHealth / MaxHealth);

			InvisibleAnimation();
			bCharacterInvincible = true;	
			UE_LOG(LogTemp,Warning,TEXT("%s: Health Left = %f"), *GetName(), CurrentHealth);
		}
	}else{
		CurrentHealth -= FMath::Min(CurrentHealth,Damage);

		SetHealthPercentage(CurrentHealth / MaxHealth);

		UE_LOG(LogTemp,Warning,TEXT("%s: Health Left = %f"), *GetName(), CurrentHealth);
	}

	if(CurrentHealth == 0){
		if(GetController()->IsA(AQuadAIController::StaticClass())){
			
			bIAmDestroyed = true;
			End.Broadcast();
			Destroy();
			
		}else if(GetController()->IsA(APlayerController::StaticClass()))
			UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
	}
		
	return Damage;

}

//Invisible animation repeted tot times. (Animation = hide and show mesh)
void ACharacterPawnQuad::InvisibleAnimation() {
	if(NumberOfRepetitions < 8){
		NumberOfRepetitions += 1;
		bIsVisible = !bIsVisible;
		Mesh->SetVisibility(bIsVisible);
		EquipmentMesh->SetVisibility(bIsVisible);
		GetWorld()->GetTimerManager().SetTimer(InvisibleTimer,this, &ACharacterPawnQuad::InvisibleAnimation, 0.125f, false);
	}else{
		NumberOfRepetitions = 0;
		bIsVisible = true;
		Mesh->SetVisibility(bIsVisible);
		EquipmentMesh->SetVisibility(bIsVisible);
		bCharacterInvincible = false;
	}
}

// Called every frame
void ACharacterPawnQuad::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

	//Move the player if it's not interacting with an NPC.
	if(!VectorMovement.IsZero() && !bStopMovement){
		FVector NewLocation = GetActorLocation() + (VectorMovement * DeltaTime * MovementSpeed);
		AddActorLocalOffset(VectorMovement);
	}

	//Add rotation
	if(!Rotation.IsZero() && !bStopMovement){
		AddActorLocalRotation(Rotation);
	}

	//Add rotation
	if(!CameraRotation.IsZero() && !bStopMovement){
		float CurrentPitch = CameraArmComponent->GetComponentRotation().Pitch;
		if((CurrentPitch + CameraRotation.Pitch) > InitialRotation.Pitch - 20 && (CurrentPitch + CameraRotation.Pitch) < InitialRotation.Pitch + 20)
			CameraArmComponent->AddLocalRotation(CameraRotation);
	}

	if(GetController()->IsA(APlayerController::StaticClass())){
		FHitResult Hit;

		FVector EndPosition = GetActorLocation() + GetActorRotation().Vector() * MaxRange;

		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(this);

		GetWorld()->LineTraceSingleByChannel(Hit,GetActorLocation(),EndPosition,ECollisionChannel::ECC_GameTraceChannel5,CollisionParams);

		//DrawDebugLine(GetWorld(),GetActorLocation(),EndPosition, FColor::Red,true);

		AGameModeAbstract* GameMode = Cast<AGameModeAbstract>(GetWorld()->GetAuthGameMode());
		UUIWidgetDialog* DialogWidget = Cast<UUIWidgetDialog>(GameMode->GetCurrentWidgetUI());

		if(Hit.GetActor() != nullptr){
			
			InteractiveActor = Cast<APawnInteractiveClass>(Hit.GetActor());

			DialogWidget->ViewPopUp();
		
		}else{
			InteractiveActor = nullptr;
			if(DialogWidget != nullptr)
				DialogWidget->HidePopUp();
		}
	}

}

// Called to bind functionality to input
void ACharacterPawnQuad::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent){
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn",this,&ACharacterPawnQuad::RotateYaw);
	PlayerInputComponent->BindAxis("LookUp",this,&ACharacterPawnQuad::RotatePitch);

	PlayerInputComponent->BindAction("Jump",IE_Pressed,this,&ACharacterPawnQuad::Jump);
	PlayerInputComponent->BindAction("Speak",IE_Pressed,this, &ACharacterPawnQuad::Speak);
	PlayerInputComponent->BindAction("Shoot",IE_Pressed,this, &ACharacterPawnQuad::Shoot);
	PlayerInputComponent->BindAction("Rewind",IE_Pressed,this, &ACharacterPawnQuad::Rewind);

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
	Rotation.Yaw = Axis *  GetWorld()->DeltaTimeSeconds * RotationSpeed/2;
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
	
	if(AllyNPC == nullptr){
		if(!bAmIShooting){
			
			ASquaredProjectile* Projectile = GetWorld()->SpawnActor<ASquaredProjectile>(ProjectileClass,ProjectileSpawnPosition->GetComponentLocation(),ProjectileSpawnPosition->GetComponentRotation());
			
			if(Projectile != nullptr)
				Projectile->MyOwner = this;
			

			bAmIShooting = true;
			GetWorld()->GetTimerManager().SetTimer(ShotTimer,this, &ACharacterPawnQuad::SetShooting, ProjectileTimeout, false);
		}
	}
}

void ACharacterPawnQuad::SetShooting() {
	bAmIShooting = false;
}

void ACharacterPawnQuad::SetMousePointer(bool Enable) {
		APlayerController* PlayerController = Cast<APlayerController>(GetController());
		PlayerController->bShowMouseCursor = Enable;
		PlayerController->bEnableClickEvents = Enable;
		PlayerController->bEnableMouseOverEvents = Enable;
		if(Enable)
			PlayerController->SetInputMode(FInputModeGameAndUI());
		else
			PlayerController->SetInputMode(FInputModeGameOnly());
}

void ACharacterPawnQuad::SetHealthPercentage(float Percentage){
	UHealthBar* HealthWidget =  Cast<UHealthBar>(HealthWidgetComponent->GetWidget());

	if(HealthWidget != nullptr)
		HealthWidget->HealthBar->SetPercent(Percentage);
}

//Stop/Start the physics and the movement
void ACharacterPawnQuad::StopCharacter(bool Value) {
	bStopMovement = !Value;
	Collider->SetSimulatePhysics(Value);
}

void ACharacterPawnQuad::Speak() {

	AGameModeAbstract* GameMode = Cast<AGameModeAbstract>(GetWorld()->GetAuthGameMode());
	UUIWidgetDialog* DialogWidget = Cast<UUIWidgetDialog>(GameMode->GetCurrentWidgetUI());

	if(InteractiveActor != nullptr || DialogWidget->TextBox->BoxContainer->IsVisible()){
		if(bStopMovement){

			if(AllyNPC->SpeechContator != AllyNPC->QuestionAt){
				AllyNPC->SpeechContator = AllyNPC->SpeechContator + 1;
				if(AllyNPC->SpeechContator == AllyNPC->QuestionAt)
					AllyNPC->Ask();
				else
					AllyNPC->Speak();
			}

		}else
			InteractiveActor->StartInteraction();
	}
}

void ACharacterPawnQuad::Rewind() {

	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);

}
