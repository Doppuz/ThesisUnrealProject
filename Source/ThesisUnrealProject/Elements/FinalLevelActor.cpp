// Fill out your copyright notice in the Description page of Project Settings.


#include "FinalLevelActor.h"
#include "HAL/PlatformFilemanager.h"
#include "../Character/CharacterPawnQuad.h"

// Sets default values
AFinalLevelActor::AFinalLevelActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

	Collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collider"));
	Collider->SetupAttachment(Root);

	Particles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particles"));
	Particles->SetupAttachment(Root);

}

// Called when the game starts or when spawned
void AFinalLevelActor::BeginPlay(){

	Super::BeginPlay();

	Collider->OnComponentBeginOverlap.AddDynamic(this,&AFinalLevelActor::OnOverlap);
	
}

void AFinalLevelActor::OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit){

	if(OtherActor->IsA(ACharacterPawnQuad::StaticClass())){
	
    		FString CompleteFilePath = FPaths::ProjectSavedDir() + "SaveGames/CheckpointLevel1.sav"; 

			UE_LOG(LogTemp,Warning,TEXT("%s"), *CompleteFilePath);

			if (!FPlatformFileManager::Get().GetPlatformFile().DeleteFile(*CompleteFilePath)){

				UE_LOG(LogTemp,Warning, TEXT("Could Not Find File"));
				return;
			
			}
	
	}

}

