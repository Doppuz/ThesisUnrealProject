// Fill out your copyright notice in the Description page of Project Settings.


#include "FinalLevelActor.h"
#include "HAL/PlatformFilemanager.h"
#include "../Character/CharacterPawnQuad.h"
#include "Kismet/GameplayStatics.h"
#include "../GameModeAbstract.h"
#include "../CheckPoints/SaveGameBartle.h"

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

			if (USaveGameBartle* SaveGameInstance = Cast<USaveGameBartle>(UGameplayStatics::CreateSaveGameObject(USaveGameBartle::StaticClass()))){

				AGameModeAbstract* GameMode = Cast<AGameModeAbstract>(GetWorld()->GetAuthGameMode());

				//Calculate rates
				float AchieverRate = float(GameMode->GetCoins()) / float(GameMode->TotalCoins) * 100.f;
				float ExplorerRate = float(GameMode->GetEnemies()) / float(GameMode->TotalEnemies) * 100.f;
				float KillerRate = float(GameMode->GetAllies()) / float(GameMode->TotalAllies) * 100.f;
				float SocializerRate = float(GameMode->GetStatues()) / float(GameMode->TotalStatues) * 100.f;

				TMap<Type,float> Rates = {{Type::Achiever,AchieverRate},{Type::Explorer,ExplorerRate},{Type::Killer,KillerRate},{Type::Socializer,SocializerRate}};
				TArray<Type> RatesArray;
				Rates.ValueSort([](float A, float B) {
        				return A > B; // sort in reverse
    				}
				);
				Rates.GetKeys(RatesArray);

				//Before
				UE_LOG(LogTemp,Warning,TEXT("Before"));
				UE_LOG(LogTemp,Warning,TEXT("Achiever = %f"), GameMode->Update->Types[Type::Achiever]);
				UE_LOG(LogTemp,Warning,TEXT("Killer = %f"), GameMode->Update->Types[Type::Killer]);
				UE_LOG(LogTemp,Warning,TEXT("Explorer = %f"), GameMode->Update->Types[Type::Explorer]);
				UE_LOG(LogTemp,Warning,TEXT("Socializer = %f"), GameMode->Update->Types[Type::Socializer]);

				if(FMath::Abs(Rates[RatesArray[0]] - Rates[RatesArray[3]]) > 20.f){
					
					GameMode->Update->Types[RatesArray[0]] += 10.f;
					GameMode->Update->Types[RatesArray[3]] -= 10.f;

				}

				if(FMath::Abs(Rates[RatesArray[1]] - Rates[RatesArray[2]]) > 20.f){
					
					GameMode->Update->Types[RatesArray[1]] += 10.f;
					GameMode->Update->Types[RatesArray[2]] -= 10.f;

				}
				
				SaveGameInstance->Achiever = GameMode->Update->Types[Type::Achiever];
				SaveGameInstance->Killer = GameMode->Update->Types[Type::Killer];
				SaveGameInstance->Explorer = GameMode->Update->Types[Type::Explorer];
				SaveGameInstance->Socializer = GameMode->Update->Types[Type::Socializer];

				UE_LOG(LogTemp,Warning,TEXT("After"));
				UE_LOG(LogTemp,Warning,TEXT("Achiever = %f"), GameMode->Update->Types[Type::Achiever]);
				UE_LOG(LogTemp,Warning,TEXT("Killer = %f"), GameMode->Update->Types[Type::Killer]);
				UE_LOG(LogTemp,Warning,TEXT("Explorer = %f"), GameMode->Update->Types[Type::Explorer]);
				UE_LOG(LogTemp,Warning,TEXT("Socializer = %f"), GameMode->Update->Types[Type::Socializer]);

				// Start async save process.
				UGameplayStatics::AsyncSaveGameToSlot(SaveGameInstance, "Bartle", 0);

			}

			if (!FPlatformFileManager::Get().GetPlatformFile().DeleteFile(*CompleteFilePath)){

				UE_LOG(LogTemp,Warning, TEXT("Could Not Find File"));
				return;
			
			}
	
	}

}

