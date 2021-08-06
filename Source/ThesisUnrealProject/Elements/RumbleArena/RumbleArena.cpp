// Fill out your copyright notice in the Description page of Project Settings.


#include "RumbleArena.h"
#include "Components/BoxComponent.h"

// Sets default values
ARumbleArena::ARumbleArena()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	
	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Collider->SetupAttachment(RootComponent);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collider);

	SpawnPositions = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPos"));
	SpawnPositions->SetupAttachment(RootComponent);

	FirstSpawnPosition = CreateDefaultSubobject<USceneComponent>(TEXT("FirstPos"));
	FirstSpawnPosition->SetupAttachment(SpawnPositions);

	SecondSpawnPosition = CreateDefaultSubobject<USceneComponent>(TEXT("SecondPos"));
	SecondSpawnPosition->SetupAttachment(SpawnPositions);

	ThirdSpawnPosition = CreateDefaultSubobject<USceneComponent>(TEXT("ThirdPos"));
	ThirdSpawnPosition->SetupAttachment(SpawnPositions);

	FourthSpawnPosition = CreateDefaultSubobject<USceneComponent>(TEXT("FourthPos"));
	FourthSpawnPosition->SetupAttachment(SpawnPositions);

	RewardSpawnPosition = CreateDefaultSubobject<USceneComponent>(TEXT("RewardPos"));
	RewardSpawnPosition->SetupAttachment(SpawnPositions);

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
		
		if(CheckAllEnemyDeath())
			
			EndArena.Broadcast();

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

