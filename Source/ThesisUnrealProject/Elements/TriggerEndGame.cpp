// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerEndGame.h"
#include "Components/BoxComponent.h"
#include "../Projectile/SquaredProjectile.h"
#include "../Character/AICharacterPawnQuad.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/LevelStreaming.h"
#include "Components/SpotLightComponent.h"

// Sets default values
ATriggerEndGame::ATriggerEndGame(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LightOn = true;
}


// Called when the game starts or when spawned
void ATriggerEndGame::BeginPlay(){
	
	Super::BeginPlay();

}

void ATriggerEndGame::OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit) {
	
	if(OtherActor->IsA(ACharacterPawnQuad::StaticClass())){
		ACharacterPawnQuad* MyPawn = Cast<ACharacterPawnQuad>(OtherActor);
		
		if(MyPawn->GetController()->IsA(APlayerController::StaticClass())){

    		UGameplayStatics::GetPlayerController(GetWorld(),0)->SetInputMode(FInputModeUIOnly());
			//Cast<APlayerController>(MyPawn->GetController())->SetPause(true);

		}
	}

}

// Called every frame
void ATriggerEndGame::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

}