// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeLevel.h"
#include "Components/BoxComponent.h"

// Sets default values
ACubeLevel::ACubeLevel(){
	
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	RootComponent = Collider;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collider);

}
