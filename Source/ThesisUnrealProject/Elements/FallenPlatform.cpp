// Fill out your copyright notice in the Description page of Project Settings.


#include "FallenPlatform.h"
#include "Components/BoxComponent.h"

// Sets default values
AFallenPlatform::AFallenPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	PlatformCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Coin Collider"));
	PlatformCollider->SetupAttachment(RootComponent);

	PlatformCollider->SetCollisionProfileName("BlockAll");
	PlatformCollider->SetGenerateOverlapEvents(false);
	PlatformCollider->SetNotifyRigidBodyCollision(true);

	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Coin Mesh"));
	PlatformMesh->SetupAttachment(PlatformCollider);

	bFall = false;
	bIsFallen = false;
	Speed = 0.f;
}

// Called when the game starts or when spawned
void AFallenPlatform::BeginPlay(){

	Super::BeginPlay();

	PlatformCollider->OnComponentHit.AddDynamic(this, &AFallenPlatform::OnHit);

}

// Called every frame
void AFallenPlatform::Tick(float DeltaTime){
	
	Super::Tick(DeltaTime);

	if(bFall)
		PlatformCollider->AddLocalOffset(-PlatformCollider->GetUpVector() * Speed * DeltaTime);
}

void AFallenPlatform::ShakingActor(float DeltaTime) {
	
	
	if(!bIsFallen){
		if(bIsShaking){
			
			if(bLeft){
				if(GetActorLocation().Y >= StartPosition.Y + ShakeDistance || GetActorLocation().Y <= StartPosition.Y - ShakeDistance){
					ShakeSpeed = -ShakeSpeed;
					AddActorLocalOffset(GetActorRightVector() * ShakeSpeed * DeltaTime);
				}else{
					AddActorLocalOffset(GetActorRightVector() * ShakeSpeed * DeltaTime);
				}
			}else{
				if(GetActorLocation().X >= StartPosition.X + ShakeDistance || GetActorLocation().X <= StartPosition.X - ShakeDistance){
					ShakeSpeed = -ShakeSpeed;
					AddActorLocalOffset(GetActorForwardVector() * ShakeSpeed * DeltaTime);
				}else{
					AddActorLocalOffset(GetActorForwardVector() * ShakeSpeed * DeltaTime);
				}
			}

		}else{
			SetActorLocation(StartPosition);
		}
	}
}

void AFallenPlatform::StartFalling() {
	Speed = 2000.f;
}

void AFallenPlatform::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {


	if(OtherActor->IsA(APawn::StaticClass())){
		if(Cast<APawn>(OtherActor)->GetController()->IsA(APlayerController::StaticClass())){
			bFall = true;
			bIsFallen = true;	
			FallenDelegate.Broadcast();
			GetWorld()->GetTimerManager().SetTimer(FallenTimer,this,&AFallenPlatform::StartFalling,1.f,false);
		}
	}

}



