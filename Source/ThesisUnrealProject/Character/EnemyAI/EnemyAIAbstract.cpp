// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIAbstract.h"
#include "Kismet/GameplayStatics.h"
#include "../../GameModeAbstract.h"

int AEnemyAIAbstract::IDCounter = 0;

// Sets default values
AEnemyAIAbstract::AEnemyAIAbstract(){

 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bIAmDestroyed = false;
	bSpawnCoin = false;

}

// Called when the game starts or when spawned
void AEnemyAIAbstract::BeginPlay(){
	
	Super::BeginPlay();

	IDEnemy = IDCounter;
	IDCounter = (IDCounter + 1) % 50000;

	InitialPos = GetActorLocation();

	UGameplayStatics::GetPlayerPawn(GetWorld(),0)->MoveIgnoreActorAdd(this);

	if(!bNoIncrease){
		
		AGameModeAbstract* GameMode = Cast<AGameModeAbstract>(GetWorld()->GetAuthGameMode());

		if(!bSpawnCoin)
			GameMode->TotalEnemies += 1;

	}
	
}

// Called every frame
void AEnemyAIAbstract::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyAIAbstract::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) 
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
