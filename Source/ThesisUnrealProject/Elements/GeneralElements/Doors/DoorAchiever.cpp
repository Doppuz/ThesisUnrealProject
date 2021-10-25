// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorAchiever.h"
#include "../../Destructible/GenericDestructibleElements.h"
#include "../../Key/KeyActor.h"
#include "../../../Character/EnemyAI/EnemyAIAbstract.h"


ADoorAchiever::ADoorAchiever() {

    SpawnPos0 = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPos0"));
	SpawnPos0->SetupAttachment(RootComponent);

    SpawnPos1 = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPos1"));
	SpawnPos1->SetupAttachment(RootComponent);

    SpawnPos2 = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPos2"));
	SpawnPos2->SetupAttachment(RootComponent);

    SpawnPos3 = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPos3"));
	SpawnPos3->SetupAttachment(RootComponent);
    
    SpawnPos4 = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPos4"));
	SpawnPos4->SetupAttachment(RootComponent);

    KeyPosition = FVector::ZeroVector;
    
}

void ADoorAchiever::BeginPlay() {

    Super::BeginPlay();

    //If needed when I spawn it from checkpoints
    if(!bCheckpoint){
        DestrActors.Add(GetWorld()->SpawnActor<AGenericDestructibleElements>(DestrElem[0],SpawnPos1->GetComponentLocation(),SpawnPos1->GetComponentRotation()));
        DestrActors.Add(GetWorld()->SpawnActor<AGenericDestructibleElements>(DestrElem[0],SpawnPos2->GetComponentLocation(),SpawnPos2->GetComponentRotation()));
        DestrActors.Add(GetWorld()->SpawnActor<AGenericDestructibleElements>(DestrElem[0],SpawnPos3->GetComponentLocation(),SpawnPos3->GetComponentRotation()));
        DestrActors.Add(GetWorld()->SpawnActor<AGenericDestructibleElements>(DestrElem[0],SpawnPos4->GetComponentLocation(),SpawnPos4->GetComponentRotation()));

        AEnemyAIAbstract* Enemy = GetWorld()->SpawnActor<AEnemyAIAbstract>(Enemies[FMath::RandRange(0, Enemies.Num() - 1)],SpawnPos0->GetComponentLocation(),SpawnPos0->GetComponentRotation());
        Enemy->bSpawnCoin = true;

        FAttachmentTransformRules TransformRules(EAttachmentRule::KeepWorld,true);
        Enemy->AttachToActor(this,TransformRules);

        int NumExtr = FMath::RandRange(0,DestrActors.Num() - 1);
        DestrActors[NumExtr]->SpawnActor = KeyClass;
        DestrActors[NumExtr]->DestrDelegate.AddDynamic(this, &ADoorAchiever::SpawnKey);

    }

    //Very Unlikely to be used, usefull only when u destroy the barrel and don't pick up the key.
    if(KeyPosition != FVector::ZeroVector && !bOpenDoor){
        AKeyActor* Elem = GetWorld()->SpawnActor<AKeyActor>(KeyClass,KeyPosition, FRotator::ZeroRotator);
        Cast<AKeyActor>(Elem)->KeyDelegate.AddDynamic(this,&ADoorAchiever::OpenDoor);
    }
    
}

void ADoorAchiever::SpawnKey(AActor* Elem) {

    KeyPosition = Elem->GetActorLocation();
    Cast<AKeyActor>(Elem)->KeyDelegate.AddDynamic(this,&ADoorAchiever::OpenDoor);
    
}
