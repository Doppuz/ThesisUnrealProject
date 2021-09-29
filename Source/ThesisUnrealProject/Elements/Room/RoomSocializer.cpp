// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomSocializer.h"
#include "../../Character/AllyAI/AICharacterPawnQuad.h"
#include "../../Character/AllyAI/PawnInteractiveClass.h"

void ARoomSocializer::BeginPlay() {

    Super::BeginPlay();

    InteractiveActor->Speech = TArray<FString>{"You are going to fight some enemies in a battle royale with a number of rounds.", "You are not alone, there is a friend that will hel you.", "-"};
	InteractiveActor->QuestionAt = 2;

}   

void ARoomSocializer::Start() {
    
    Super::Start();

    FVector Location = InteractiveActor->GetActorLocation();
    Location.Z = -18.f;

    GetWorld()->SpawnActor<AAICharacterPawnQuad>(AICharacterPawnQuadClass,Location, FRotator::ZeroRotator);

}
