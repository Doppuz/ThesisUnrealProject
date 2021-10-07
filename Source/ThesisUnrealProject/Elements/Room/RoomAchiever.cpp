// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomAchiever.h"
#include "../../Elements/GeneralElements/CoinController.h"
#include "Kismet/GameplayStatics.h"
#include "../GeneralElements/Doors/Door.h"
#include "../../Character/EnemyAI/AIShooterPawn.h"


ARoomAchiever::ARoomAchiever() {
    
    SpawnPositions = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPos"));
	SpawnPositions->SetupAttachment(RootComponent);

	StartSpawnPosition = CreateDefaultSubobject<USceneComponent>(TEXT("StartPos"));
	StartSpawnPosition->SetupAttachment(SpawnPositions);

	MiddleSpawnPosition = CreateDefaultSubobject<USceneComponent>(TEXT("MiddlePos"));
	MiddleSpawnPosition->SetupAttachment(SpawnPositions);

    CoinsCollected = 0;
    TotalCoins = 0;
}

void ARoomAchiever::BeginPlay() {
    
    Super::BeginPlay();

    ACoinController* Coin;

    FAttachmentTransformRules Rules(EAttachmentRule::KeepWorld,false);

    for(int i = 0; i < 9; i++){
        
        for(int j = 0; j < 9; j++){
            
            float NumExtr = FMath::RandRange(0.f,10.f);
            if((i == 0 && j == 0) || NumExtr < 7.5f){
            
                Coin = GetWorld()->SpawnActor<ACoinController>(CoinClass, FVector(StartSpawnPosition->GetComponentLocation().X - 310 * i,StartSpawnPosition->GetComponentLocation().Y - 310.f * j, 80.f), FRotator::ZeroRotator);
                Coin->CollectedDelegate.AddDynamic(this,&ARoomAchiever::OnCoinCollect);
                Coin->AttachToActor(this,Rules);
                TotalCoins += 1;

            }else if(NumExtr < 9.7f)
                GetWorld()->SpawnActor<AActor>(MetalCrateClass, FVector(StartSpawnPosition->GetComponentLocation().X - 310 * i,StartSpawnPosition->GetComponentLocation().Y - 310.f * j, 50.f), FRotator::ZeroRotator)->AttachToActor(this,Rules);
            else{
            
                AAIShooterPawn* Shooter = GetWorld()->SpawnActor<AAIShooterPawn>(ShooterPawnClass, FVector(StartSpawnPosition->GetComponentLocation().X - 310 * i,StartSpawnPosition->GetComponentLocation().Y - 310.f * j, 110.f), FRotator::ZeroRotator);
                Shooter->bSpawnCoin = true;
                Shooter->AttachToActor(this,Rules);

            }
        }

    }

}


void ARoomAchiever::OnCoinCollect() {

    CoinsCollected += 1;

    if(CoinsCollected == TotalCoins){
        
        APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
        PlayerPawn->SetActorLocation(EndPos);
        Door->bOpenDoor = true;

    }
    
}
