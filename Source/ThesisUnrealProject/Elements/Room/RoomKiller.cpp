// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomKiller.h"
#include "../../Character/AllyAI/PawnInteractiveClass.h"

// Sets default values
ARoomKiller::ARoomKiller()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

	PortalSpawnPosition = CreateDefaultSubobject<USceneComponent>(TEXT("RewardPos"));
	PortalSpawnPosition->SetupAttachment(SpawnPositions);

	TurnNumbers = 3;
}

// Called when the game starts or when spawned
void ARoomKiller::BeginPlay(){

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

	InteractiveActor = GetWorld()->SpawnActor<APawnInteractiveClass>(NpcClass,PortalSpawnPosition->GetComponentLocation() + FVector(0.f,0.f,100.f),FRotator::ZeroRotator);
	InteractiveActor->LeftChoice.AddDynamic(this,&ARoomKiller::Start);

}

// Called every frame
void ARoomKiller::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

	if(bStart){

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

}

void ARoomKiller::Start() {
	
    InteractiveActor->Destroy();
	bStart = true;
}

bool ARoomKiller::CheckAllEnemyDeath() {

	for(AEnemyAIAbstract* Enemy: Enemies){
		if(!(Enemy == nullptr) && !Enemy->bIAmDestroyed)
			return false;
	}

	Enemies.Empty();

	TurnNumbers -= 1;

	return true;
}


