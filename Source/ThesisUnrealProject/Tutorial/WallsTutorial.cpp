// Fill out your copyright notice in the Description page of Project Settings.


#include "WallsTutorial.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWallsTutorial::AWallsTutorial(){

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AWallsTutorial::BeginPlay(){

	Super::BeginPlay();

	UGameplayStatics::GetPlayerPawn(GetWorld(),0)->MoveIgnoreActorAdd(this);

}
