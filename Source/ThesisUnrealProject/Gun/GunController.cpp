// Fill out your copyright notice in the Description page of Project Settings.


#include "GunController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGunController::AGunController(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));
	SkeletalMesh->SetupAttachment(RootComponent);

}

void AGunController::PullTrigger() {
	UGameplayStatics::SpawnEmitterAttached(MuzzleEffect,SkeletalMesh,TEXT("MuzzleFlashSocket"));
}

// Called when the game starts or when spawned
void AGunController::BeginPlay(){
	Super::BeginPlay();
}

// Called every frame
void AGunController::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
}

