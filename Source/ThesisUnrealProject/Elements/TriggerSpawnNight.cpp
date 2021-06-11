// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerSpawnNight.h"
#include "Components/BoxComponent.h"
#include "../Projectile/SquaredProjectile.h"
#include "../Character/AICharacterPawnQuad.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/LevelStreaming.h"
#include "../GameModeTutorial.h"

// Sets default values
ATriggerSpawnNight::ATriggerSpawnNight(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


// Called when the game starts or when spawned
void ATriggerSpawnNight::BeginPlay(){
	
	Super::BeginPlay();

}

// Called every frame
void ATriggerSpawnNight::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

}

void ATriggerSpawnNight::OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit) {

	if(OtherActor->IsA(ACharacterPawnQuad::StaticClass())){
		APawn* MyPawn = Cast<APawn>(OtherActor);
		
		if(MyPawn->GetController()->IsA(APlayerController::StaticClass())){
    		FLatentActionInfo LatentInfo;
		
			AGameModeTutorial* GameMode = Cast<AGameModeTutorial>(GetWorld()->GetAuthGameMode());

			if(GameMode->bDay){
				
				UGameplayStatics::UnloadStreamLevel(this, TEXT("Day"), LatentInfo, true);
				//UGameplayStatics::LoadStreamLevel(this, TEXT("Night"), true, true, LatentInfo);
				GameMode->bDay = false;
				UE_LOG(LogTemp,Warning,TEXT("1"));
				
			}else{
				
				//UGameplayStatics::UnloadStreamLevel(this, TEXT("Night"), LatentInfo, true);
				UGameplayStatics::LoadStreamLevel(this, TEXT("Day"), true, true, LatentInfo);
				GameMode->bDay = true;
				UE_LOG(LogTemp,Warning,TEXT("2"));
			
			}

		}
	}

}
