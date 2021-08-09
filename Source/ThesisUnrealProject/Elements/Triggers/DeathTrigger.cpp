// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathTrigger.h"
#include "Components/BoxComponent.h"
#include "../../Projectile/SquaredProjectile.h"
#include "../../Character/CharacterPawnQuad.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADeathTrigger::ADeathTrigger(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


// Called when the game starts or when spawned
void ADeathTrigger::BeginPlay(){
	
	Super::BeginPlay();

}

// Called every frame
void ADeathTrigger::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

}

void ADeathTrigger::OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit) {

	if(OtherActor->IsA(ACharacterPawnQuad::StaticClass())){
		ACharacterPawnQuad* MyPawn = Cast<ACharacterPawnQuad>(OtherActor);
		if(MyPawn->GetController()->IsA(APlayerController::StaticClass())){
			UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
		}
	}

}