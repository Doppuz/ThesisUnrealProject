// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerMap.h"
#include "../../Character/CharacterPawnQuad.h"
#include "../../GameModeAbstract.h"

// Called when the game starts or when spawned
void ATriggerMap::BeginPlay(){
	
	Super::BeginPlay();
	
	AGameModeAbstract* GameMode = Cast<AGameModeAbstract>(GetWorld()->GetAuthGameMode());
	GameMode->TotalMap += 1;

}

void ATriggerMap::OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit) {

    if(OtherActor->IsA(ACharacterPawnQuad::StaticClass())){

        AGameModeAbstract* GameMode = Cast<AGameModeAbstract>(GetWorld()->GetAuthGameMode());
        GameMode->IncreaseMap();
        Destroy();

    }

}
