// Fill out your copyright notice in the Description page of Project Settings.


#include "ShakeActor.h"
#include "../Elements/DestructibleElements.h"
#include "Components/BoxComponent.h"

// Sets default values
AShakeActor::AShakeActor(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	ShakingActor = CreateDefaultSubobject<UChildActorComponent>(TEXT("ShakingActor"));
	ShakingActor->SetupAttachment(Root);

	LeftTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftTrigger"));
	LeftTrigger->SetupAttachment(Root);
	LeftTrigger->SetCollisionProfileName("TriggerWall");

	RightTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("RightTrigger"));
	RightTrigger->SetupAttachment(Root);
	RightTrigger->SetCollisionProfileName("TriggerWall");

	ShakeSpeed = 2.f;
	IntervalTime = 1.f;
	bIsShaking = false;
	ShakeLeft = true;

}

// Called when the game starts or when spawned
void AShakeActor::BeginPlay(){

	Super::BeginPlay();

	StartPosition = ShakingActor->GetComponentLocation();

	LeftTrigger->OnComponentBeginOverlap.AddDynamic(this,&AShakeActor::OnOverlap);
	RightTrigger->OnComponentBeginOverlap.AddDynamic(this,&AShakeActor::OnOverlap);

	WaitShake();
	

}

// Called every frame
void AShakeActor::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

	Shake(DeltaTime);

}

void AShakeActor::EnableShake() {
	bIsShaking = true;	
	GetWorld()->GetTimerManager().SetTimer(ShakeTimer,this,&AShakeActor::WaitShake,IntervalTime,false);
}

void AShakeActor::WaitShake() {
	bIsShaking = false;	
	GetWorld()->GetTimerManager().SetTimer(ShakeTimer,this,&AShakeActor::EnableShake,IntervalTime,false);
}

void AShakeActor::Shake(float DeltaTime) {

	if(bIsShaking){
		
		if(ShakeLeft)
			ShakingActor->AddLocalOffset(ShakingActor->GetRightVector() * ShakeSpeed);
		else
			ShakingActor->AddLocalOffset(ShakingActor->GetForwardVector() * ShakeSpeed);
	}else{
		SetActorLocation(StartPosition);
	}

}

void AShakeActor::OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit) {

	if(OtherActor == ShakingActor->GetChildActor())
		ShakeSpeed = -ShakeSpeed;

}
