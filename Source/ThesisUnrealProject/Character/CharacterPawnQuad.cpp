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
#include "../AI/QuadAIController.h"
#include "DrawDebugHelpers.h"
#include "PawnInteractiveClass.h"
#include "../GameModeTutorial.h"
#include "../UI/UIWidgetDialog.h"
#include "Components/TextBlock.h"
#include "Engine/TriggerVolume.h"
#include "Engine/LatentActionManager.h"

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

	MovementSpeed = 400.f;
	RotationSpeed = 400.f;
	JumpForce = 500.f;
	bAmIJump = false;
	bAmIShooting = false;
	ProjectileTimeout = 0.5f;
	MaxHealth = 30;
	AllyNPC = nullptr;
	MaxRange = 300.f;
	InteractiveActor = nullptr;
	bStopMovement = false;
	MaxRandomDistance = 300.f;
}


// Called when the game starts or when spawned
void ACharacterPawnQuad::BeginPlay(){
	Super::BeginPlay();

	Health = MaxHealth;
	InitialRotation = CameraArmComponent->GetComponentRotation();
	Collider->OnComponentBeginOverlap.AddDynamic(this,&ACharacterPawnQuad::OnOverlap);
	//Collider->OnComponentHit.AddDynamic(this, &ACharacterPawnQuad::OnHit);
}

//Add damage. If healt == 0, destroy the actor. Switch case to apply changes to the manager.
float ACharacterPawnQuad::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) {
	
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Health -= FMath::Min(Health,Damage);

	UE_LOG(LogTemp,Warning,TEXT("%s: Health Left = %f"), *GetName(), Health);

	if(Health == 0){
		if(GetController()->IsA(AQuadAIController::StaticClass())){
			Destroy();
			AGameModeTutorial* GameMode = Cast<AGameModeTutorial>(GetWorld()->GetAuthGameMode());
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
			}
		}else if(GetController()->IsA(APlayerController::StaticClass()))
			UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
	}
		
	return Damage;

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

		AGameModeTutorial* GameMode = Cast<AGameModeTutorial>(GetWorld()->GetAuthGameMode());
		UUIWidgetDialog* DialogWidget = Cast<UUIWidgetDialog>(GameMode->GetCurrentWidgetUI());

		if(Hit.GetActor() != nullptr){
			
			InteractiveActor = Cast<APawnInteractiveClass>(Hit.GetActor());

			DialogWidget->ViewPopUp();
		
		}else{
			InteractiveActor = nullptr;
			DialogWidget->HidePopUp();
		}
	}else{
		/*
		APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);

		FVector NewPos = (-GetActorLocation() + PlayerPawn->GetActorLocation());
		NewPos.Z = 0;
    	NewPos.Normalize();

    	SetActorRotation(FMath::RInterpTo(GetActorRotation(),NewPos.Rotation(),DeltaTime * 100,0.4));*/
	}
}

// Called to bind functionality to input
void ACharacterPawnQuad::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent){
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn",this,&ACharacterPawnQuad::RotateYaw);
	PlayerInputComponent->BindAxis("LookUp",this,&ACharacterPawnQuad::RotatePitch);

	PlayerInputComponent->BindAction("Jump",IE_Pressed,this,&ACharacterPawnQuad::Jump);
	PlayerInputComponent->BindAction("Speak",IE_Released,this, &ACharacterPawnQuad::Speak);
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
	
	if(AllyNPC == nullptr){
		if(!bAmIShooting){

			ASquaredProjectile* Projectile = GetWorld()->SpawnActor<ASquaredProjectile>(ProjectileClass,ProjectileSpawnPosition->GetComponentLocation(),ProjectileSpawnPosition->GetComponentRotation());

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
		/*if(Enable)
			PlayerController->SetInputMode(FInputModeUIOnly());
		else
			PlayerController->SetInputMode(FInputModeGameOnly());*/
}

void ACharacterPawnQuad::OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit) {

	//Collect coins
	if(OtherActor->IsA(ACoinController::StaticClass())){
	
		AGameModeTutorial* GameMode = Cast<AGameModeTutorial>(GetWorld()->GetAuthGameMode());
		GameMode->IncreaseCoins();
		int CoinID = Cast<ACoinController>(OtherActor)->ID;
		OtherActor->Destroy();
		UUIWidgetDialog* UI = Cast<UUIWidgetDialog>(GameMode->GetCurrentWidgetUI());
		if(UI->CoinText->GetVisibility() == ESlateVisibility::Hidden)
			UI->CoinText->SetVisibility(ESlateVisibility::Visible);
		UI->SetCoinText(GameMode->GetCoins());

		switch(CoinID){
			case 0:
				GameMode->SetDoorOpen(9);
				break;
			default:
				break;
		}
	
	}else if(OtherActor->IsA(ATriggerVolume::StaticClass()) && OtherActor->Tags[0] == TEXT("TriggerExplorer")){
		AGameModeTutorial* GameMode = Cast<AGameModeTutorial>(GetWorld()->GetAuthGameMode());
		if(!GameMode->TriggerVolumes.Contains(OtherActor)){
			GameMode->TriggerVolumes.Add(OtherActor);
		}
	}

}

void ACharacterPawnQuad::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {
	
}

void ACharacterPawnQuad::Speak() {
	if(InteractiveActor != nullptr){
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

