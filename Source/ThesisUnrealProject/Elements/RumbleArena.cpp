// Fill out your copyright notice in the Description page of Project Settings.


#include "RumbleArena.h"
#include "Components/BoxComponent.h"
#include "../Character/EnemyAIAbstract.h"
#include "ActorSpawner.h"
#include "ActorSpawnerWithOwner.h"
#include "CoinController.h"

// Sets default values
ARumbleArena::ARumbleArena()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	//RootComponent = Root;
	
	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	RootComponent = Collider;
	//Collider->SetupAttachment(RootComponent);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	FirstSpawnPosition = CreateDefaultSubobject<USceneComponent>(TEXT("FirstPos"));
	FirstSpawnPosition->SetupAttachment(RootComponent);

	SecondSpawnPosition = CreateDefaultSubobject<USceneComponent>(TEXT("SecondPos"));
	SecondSpawnPosition->SetupAttachment(RootComponent);

	ThirdSpawnPosition = CreateDefaultSubobject<USceneComponent>(TEXT("ThirdPos"));
	ThirdSpawnPosition->SetupAttachment(RootComponent);

	FourthSpawnPosition = CreateDefaultSubobject<USceneComponent>(TEXT("FourthPos"));
	FourthSpawnPosition->SetupAttachment(RootComponent);

	RewardSpawnPosition = CreateDefaultSubobject<USceneComponent>(TEXT("RewardPos"));
	RewardSpawnPosition->SetupAttachment(RootComponent);

	TurnNumbers = 3;
}

// Called when the game starts or when spawned
void ARumbleArena::BeginPlay(){
	Super::BeginPlay();
	
	//Spawn the enemies spawners.
	Spawners.Add(GetWorld()->SpawnActor<AActorSpawner>(SpawnerClass,FirstSpawnPosition->GetComponentLocation(),
		FirstSpawnPosition->GetComponentRotation()));

	Spawners.Add(GetWorld()->SpawnActor<AActorSpawner>(SpawnerClass,SecondSpawnPosition->GetComponentLocation(),
		SecondSpawnPosition->GetComponentRotation()));

	Spawners.Add(GetWorld()->SpawnActor<AActorSpawner>(SpawnerClass,ThirdSpawnPosition->GetComponentLocation(),
		ThirdSpawnPosition->GetComponentRotation()));
		
	Spawners.Add(GetWorld()->SpawnActor<AActorSpawner>(SpawnerClass,FourthSpawnPosition->GetComponentLocation(),
		FourthSpawnPosition->GetComponentRotation()));

	//Assign the actor to the riddle actor to solve the puzzle.
	if(RiddleActor != nullptr){
		for(AActorSpawner* Spawner: Spawners){
			Cast<AActorSpawnerWithOwner>(Spawner)->RiddleActor = RiddleActor;
		}
	}

}

// Called every frame
void ARumbleArena::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

	if(TurnNumbers > 0){
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
				Enemies.Add(Enemy);
			
			}
		}

	}
	
	if(TurnNumbers == 0){
		if(CheckAllEnemyDeath()){

		//For example, it opend the door.
		if(RiddleActor != nullptr)
			RiddleActor->bUseTurnMethodology = false;

		//It spawns the coin.
		if(RewardClass != nullptr)
			GetWorld()->SpawnActor<ACoinController>(RewardClass,RewardSpawnPosition->GetComponentLocation(),
				RewardSpawnPosition->GetComponentRotation());
		}

	}

}

bool ARumbleArena::CheckAllEnemyDeath() {

	for(AEnemyAIAbstract* Enemy: Enemies){
		if(!(Enemy == nullptr) && !Enemy->bIAmDestroyed)
			return false;
	}

	Enemies.Empty();

	TurnNumbers -= 1;

	return true;
}

