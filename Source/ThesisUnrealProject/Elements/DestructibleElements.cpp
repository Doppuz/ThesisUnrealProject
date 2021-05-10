// Fill out your copyright notice in the Description page of Project Settings.


#include "DestructibleElements.h"
#include "DestructibleComponent.h"

// Sets default values
ADestructibleElements::ADestructibleElements(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	DestructibleMesh = CreateDefaultSubobject<UDestructibleComponent>(TEXT("DestructibleMesh"));
	DestructibleMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ADestructibleElements::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADestructibleElements::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

