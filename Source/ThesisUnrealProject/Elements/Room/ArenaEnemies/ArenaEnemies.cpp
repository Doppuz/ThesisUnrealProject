// Fill out your copyright notice in the Description page of Project Settings.


#include "ArenaEnemies.h"
#include "../../GeneralElements/CoinController.h"
#include "../../GeneralElements/Doors/Door.h"
#include "../../../Character/EnemyAI/EnemyAIAbstract.h"
#include "Components/BoxComponent.h"

AArenaEnemies::AArenaEnemies() {

    SpawnPositions = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPos"));
    SpawnPositions->SetupAttachment(RootComponent);

    Spawn1 = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn1"));
    Spawn1->SetupAttachment(SpawnPositions);
    
    Spawn2 = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn2"));
    Spawn2->SetupAttachment(SpawnPositions);
    
    Spawn3 = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn3"));
    Spawn3->SetupAttachment(SpawnPositions);
    
    Spawn4 = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn4"));
    Spawn4->SetupAttachment(SpawnPositions);
    
    Spawn5 = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn5"));
    Spawn5->SetupAttachment(SpawnPositions);
    
    Spawn6 = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn6"));
    Spawn6->SetupAttachment(SpawnPositions);
    
    Spawn7 = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn7"));
    Spawn7->SetupAttachment(SpawnPositions);
    
    Spawn8 = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn8"));
    Spawn8->SetupAttachment(SpawnPositions);

    Spawn9 = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn9"));
    Spawn9->SetupAttachment(SpawnPositions);

    EnemiesNumber = 4;
    CoinsCollected = 0;
    
}

void AArenaEnemies::BeginPlay() {
    
    Super::BeginPlay();

    SpawnEnemies();

}

void AArenaEnemies::SpawnEnemies() {

    TArray<USceneComponent*> Spawns;
    SpawnPositions->GetChildrenComponents(true,Spawns);

    for(int i = 0; i < EnemiesNumber; i++){
        
        int RandomSpawnNumber = FMath::RandRange(0,Spawns.Num() - 1);
        int RandomEnemy = FMath::RandRange(0,EnemiesClass.Num() - 1);

        if(EnemiesClass.Num() == 0)
            return;

        FVector SpawnPos = Spawns[RandomSpawnNumber]->GetComponentLocation();
        FRotator SpawnRot = Spawns[RandomSpawnNumber]->GetComponentRotation();
        TSubclassOf<AEnemyAIAbstract> A = EnemiesClass[RandomEnemy];
        AEnemyAIAbstract* Enemy = GetWorld()->SpawnActor<AEnemyAIAbstract>(EnemiesClass[RandomEnemy],SpawnPos,SpawnRot);
        Enemy->End.AddDynamic(this,&AArenaEnemies::SpawnCoins);

        Spawns.RemoveAt(RandomSpawnNumber);

    }
    
}

void AArenaEnemies::SpawnCoins(AEnemyAIAbstract* Enemy) {
    
    ACoinController* Coin = GetWorld()->SpawnActor<ACoinController>(CoinClass,Enemy->GetActorLocation(),Enemy->GetActorRotation());
    Coin->CollectedDelegate.AddDynamic(this,&AArenaEnemies::OpenDoor);

}

void AArenaEnemies::OpenDoor() {
    
    CoinsCollected += 1;

    if(CoinsCollected == EnemiesNumber){
        
        Super::OpenDoor();

    }

}
