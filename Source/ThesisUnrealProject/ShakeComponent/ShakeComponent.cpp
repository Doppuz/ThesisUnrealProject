// Fill out your copyright notice in the Description page of Project Settings.


#include "ShakeComponent.h"
#include "Components/BoxComponent.h"
#include "../Character/CharacterPawnQuad.h"

// Sets default values for this component's properties
UShakeComponent::UShakeComponent(){

	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
    
	ShakeRotation = 0.8f;
	IntervalTime = 1.f;

}


// Called when the game starts
void UShakeComponent::BeginPlay(){

	Super::BeginPlay();

	Parent = GetOwner();

	UBoxComponent* U = Parent->FindComponentByClass<UBoxComponent>();

	StartRotator = Parent->GetActorRotation();

	InitialRot = ShakeRotation;

    StartPos = Parent->GetActorLocation();
	WaitShake();
	
}


// Called every frame
void UShakeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction){

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(!bStopShaking)
        Shake(DeltaTime);
}

void UShakeComponent::EnableShake() {
    
	bIsShaking = true;	
	if (GetWorld() != nullptr)
		GetWorld()->GetTimerManager().SetTimer(ShakeTimer,this,&UShakeComponent::WaitShake,IntervalTime,false);

}

void UShakeComponent::WaitShake() {
    
	bIsShaking = false;	
	if (GetWorld() != nullptr)
		GetWorld()->GetTimerManager().SetTimer(ShakeTimer,this,&UShakeComponent::EnableShake,IntervalTime,false);

}

void UShakeComponent::Shake(float DeltaTime) {
    
    if(bIsShaking){
		
		Parent->AddActorLocalRotation(FRotator(0.f,ShakeRotation,0.f));
        ShakeRotation = -ShakeRotation;

	}else{

		Parent->SetActorRotation(StartRotator);
        ShakeRotation = InitialRot;

	}

}

void UShakeComponent::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {

	if(OtherActor->IsA(ACharacterPawnQuad::StaticClass())){
		
		bStopShaking = true;

	}

}
