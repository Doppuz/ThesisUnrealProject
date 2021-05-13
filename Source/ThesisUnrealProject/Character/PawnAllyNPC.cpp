// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnAllyNPC.h"
#include "Components/BoxComponent.h"
#include "../Elements/CoinController.h"
#include "../Elements/CrateElements.h"
#include "Blueprint/UserWidget.h"
#include "../UI/UIWidget.h"
#include "../Character/CharacterPawnQuad.h"
#include "Kismet/GameplayStatics.h"
#include "DestructibleComponent.h"
#include "../GameManager/MazegenerationPopulate.h"
#include "../Projectile/SquaredProjectile.h"
#include "Components/PrimitiveComponent.h"
#include "../AI/QuadAIController.h"
#include "../GameModeTutorial.h"

// Sets default values
APawnAllyNPC::APawnAllyNPC(){
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	TriggerDialog = CreateDefaultSubobject<UBoxComponent>(TEXT("DialogCollider"));
	TriggerDialog->SetupAttachment(RootComponent);
	TriggerDialog->SetWorldScale3D(FVector(4.f,4.f,4.f));
	TriggerDialog->SetCollisionProfileName(TEXT("Trigger"),true);

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Collider->SetupAttachment(TriggerDialog);
	Collider->SetWorldScale3D(FVector(0.3f,0.3f,0.3f));
	Collider->SetSimulatePhysics(true);
	Collider->SetCollisionProfileName(TEXT("Pawn"),true);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collider);
	Mesh->SetWorldScale3D(FVector(0.65f,0.65f,0.65f));

	ProjectileSpawnPosition = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPosition"));
	ProjectileSpawnPosition->SetupAttachment(RootComponent);

	ProjectileSpawnPosition->SetRelativeLocation(FVector(60.f,0,0));

	JumpForce = 300.f;
	bAmIJump = false;
	bAmIShooting = false;
	ProjectileTimeout = 0.5f;
	MaxHealth = 30;
}


// Called when the game starts or when spawned
void APawnAllyNPC::BeginPlay(){
	Super::BeginPlay();

	Health = MaxHealth;
	TriggerDialog->OnComponentBeginOverlap.AddDynamic(this,&APawnAllyNPC::OnBeginOverlap);
	TriggerDialog->OnComponentEndOverlap.AddDynamic(this,&APawnAllyNPC::OnEndOverlap);

}

float APawnAllyNPC::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) {
	
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Health -= FMath::Min(Health,Damage);

	UE_LOG(LogTemp,Warning,TEXT("%s: Health Left = %f"), *GetName(), Health);

	if(Health == 0 && GetController()->IsA(AQuadAIController::StaticClass()))
		Destroy();

	return Damage;

}

// Called every frame
void APawnAllyNPC::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

}

void APawnAllyNPC::Jump() {
	if(!bAmIJump){
		Collider->AddImpulse(GetActorUpVector() * JumpForce,NAME_None,true);
		bAmIJump = true;
		GetWorld()->GetTimerManager().SetTimer(JumpTimer,this,&APawnAllyNPC::SetJump,(JumpForce / 5)/100,false);
	}
}

void APawnAllyNPC::SetJump(){
	bAmIJump = false;
}

void APawnAllyNPC::Shoot() {
	if(!bAmIShooting){
		ASquaredProjectile* Projectile = GetWorld()->SpawnActor<ASquaredProjectile>(ProjectileClass,ProjectileSpawnPosition->GetComponentLocation(),ProjectileSpawnPosition->GetComponentRotation());

		Projectile->MyOwner = this;

		bAmIShooting = true;
		GetWorld()->GetTimerManager().SetTimer(ShotTimer,this, &APawnAllyNPC::SetShooting, ProjectileTimeout, false);
	}
}

void APawnAllyNPC::SetShooting() {
	bAmIShooting = false;
}

void APawnAllyNPC::OnBeginOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit) {
	if(OtherActor->IsA(ACharacterPawnQuad::StaticClass())){
		AGameModeTutorial* GameMode = Cast<AGameModeTutorial>(GetWorld()->GetAuthGameMode());
		GameMode->ChangeMenuWidget(WidgetClass);
	}

}

void APawnAllyNPC::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	if(OtherActor->IsA(ACharacterPawnQuad::StaticClass())){
		AGameModeTutorial* GameMode = Cast<AGameModeTutorial>(GetWorld()->GetAuthGameMode());
		GameMode->ChangeMenuWidget(nullptr);
	}
}
