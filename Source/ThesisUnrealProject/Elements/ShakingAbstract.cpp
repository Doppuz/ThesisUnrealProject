// Fill out your copyright notice in the Description page of Project Settings.


#include "ShakingAbstract.h"
#include "DestructibleComponent.h"
#include "../GameModeTutorial.h"
#include "Components/BoxComponent.h"

// Sets default values
AShakingAbstract::AShakingAbstract(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ShakeSpeed = 50.f;
	ShakeDistance = 100.f;
	IntervalTime = 2.f;
	bCanShake = false;
}

void AShakingAbstract::Tick(float DeltaTime) {
	
	Super::Tick(DeltaTime);

	ShakingActor(DeltaTime);

}

// Called when the game starts or when spawned
void AShakingAbstract::BeginPlay(){
	Super::BeginPlay();
	
	StartPosition = GetActorLocation();

	if(bCanShake){
		WaitShake();
	}

}

void AShakingAbstract::Shake() {
	bIsShaking = true;	
	GetWorld()->GetTimerManager().SetTimer(ShakeTimer,this,&AShakingAbstract::WaitShake,IntervalTime,false);
}

void AShakingAbstract::WaitShake() {
	bIsShaking = false;	
	GetWorld()->GetTimerManager().SetTimer(ShakeTimer,this,&AShakingAbstract::Shake,IntervalTime,false);
}

void AShakingAbstract::ShakingActor(float DeltaTime) {

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
