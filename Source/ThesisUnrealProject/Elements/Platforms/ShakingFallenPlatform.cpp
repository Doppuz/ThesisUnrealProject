// Fill out your copyright notice in the Description page of Project Settings.


#include "ShakingFallenPlatform.h"
#include "Components/BoxComponent.h"

AShakingFallenPlatform::AShakingFallenPlatform() {

    ShakeRotation = 0.8f;
	IntervalTime = 1.f;
	bIsShaking = false;
    bStopShaking = false;
    
}

void AShakingFallenPlatform::BeginPlay() {
    
    Super::BeginPlay();

    StartPos = GetActorLocation();
	WaitShake();
}

void AShakingFallenPlatform::Tick(float DeltaTime) {
    
    Super::Tick(DeltaTime);

    if(!bStopShaking)
        Shake(DeltaTime);

}

void AShakingFallenPlatform::EnableShake() {
    
	bIsShaking = true;	
	GetWorld()->GetTimerManager().SetTimer(ShakeTimer,this,&AShakingFallenPlatform::WaitShake,IntervalTime,false);

}

void AShakingFallenPlatform::WaitShake() {
    
	bIsShaking = false;	
	GetWorld()->GetTimerManager().SetTimer(ShakeTimer,this,&AShakingFallenPlatform::EnableShake,IntervalTime,false);

}

void AShakingFallenPlatform::Shake(float DeltaTime) {
    
    if(bIsShaking){
		
		SetActorRotation(FRotator(0.f,0.f,ShakeRotation));
        ShakeRotation = -ShakeRotation;

	}else{
		SetActorRotation(FRotator(0.f,0.f,0.f));
        ShakeRotation = 0.8f;
	}

}


void AShakingFallenPlatform::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {

    if(OtherActor->IsA(APawn::StaticClass())){
		if(Cast<APawn>(OtherActor)->GetController()->IsA(APlayerController::StaticClass()) && !bIsFallen){
			bStopShaking = true;
		}
	}

    Super::OnHit(HitComponent,OtherActor,OtherComp,NormalImpulse,Hit);

}
