// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorKiller.h"
#include "../../../GameModeAbstract.h"

ADoorKiller::ADoorKiller() {

	PrimaryActorTick.bCanEverTick = true;
	
    SpawnPos1 = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPos1"));
	SpawnPos1->SetupAttachment(RootComponent);
    
	SpawnPos2 = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPos2"));
	SpawnPos2->SetupAttachment(RootComponent);

    TurnNumbers = 3;

}

void ADoorKiller::BeginPlay() {

    Super::BeginPlay();

	//Spawn the enemies spawners.
	Spawners.Add(GetWorld()->SpawnActor<AActorSpawner>(SpawnerClass,SpawnPos1->GetComponentLocation(),
		SpawnPos1->GetComponentRotation()));

	Spawners.Add(GetWorld()->SpawnActor<AActorSpawner>(SpawnerClass,SpawnPos2->GetComponentLocation(),
		SpawnPos2->GetComponentRotation()));

}

void ADoorKiller::Tick(float DeltaTime) {
    
    Super::Tick(DeltaTime);

    if(TurnNumbers > 0 && !bOpenDoor){
		
		if(CheckAllEnemyDeath()){
			for(AActorSpawner* Spawner: Spawners){
				
				if(ActorsToSpawn.Num() == 0){
					UE_LOG(LogTemp,Warning,TEXT("No Enemies selected"));
					return;
				}

				if(Spawner == nullptr){
					UE_LOG(LogTemp,Warning,TEXT("No Spawner selected"));
					return;
				}

				Spawner->ActorToSpawn = ActorsToSpawn[FMath::RandRange(0,ActorsToSpawn.Num() - 1)];

				//Memorize all the enemies to be eliminated to pass the round
				AEnemyAIAbstract* Enemy = Cast<AEnemyAIAbstract>(Spawner->SpawnActor());

				if(Enemy != nullptr){
				
					Enemies.Add(Enemy);
					Enemy->End.AddDynamic(this,&ADoorKiller::EndEnemies);
					Enemy->bNoIncrease = true;

					AGameModeAbstract* GameMode = Cast<AGameModeAbstract>(GetWorld()->GetAuthGameMode());
					GameMode->TotalEnemies -= 1;

				}

			}
		}

	}
	
	if(TurnNumbers == 0){
		
		if(CheckAllEnemyDeath())
			
			bOpenDoor = true;

	}

}

void ADoorKiller::EndEnemies(AEnemyAIAbstract* Enemy){

	Enemies.Remove(Enemy);

}

bool ADoorKiller::CheckAllEnemyDeath() {
    
    if(Enemies.Num() != 0)
		return false;

	TurnNumbers -= 1;

	return true;

}

