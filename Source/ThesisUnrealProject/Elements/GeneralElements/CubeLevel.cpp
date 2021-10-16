// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeLevel.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACubeLevel::ACubeLevel(){
	
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	RootComponent = Collider;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collider);

}

	
void ACubeLevel::BeginPlay(){

	Super::BeginPlay();
	
	UGameplayStatics::GetPlayerPawn(GetWorld(),0)->MoveIgnoreActorAdd(this);

}