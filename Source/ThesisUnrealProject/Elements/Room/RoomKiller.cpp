// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomKiller.h"
#include "../../Character/AllyAI/PawnInteractiveClass.h"
#include "../../Elements/GeneralElements/Doors/Door.h"
#include "../../Elements/Portal/Portal.h"

// Sets default values
ARoomKiller::ARoomKiller()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnPositions = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPos"));
	SpawnPositions->SetupAttachment(RootComponent);

	FirstSpawnPosition = CreateDefaultSubobject<USceneComponent>(TEXT("FirstPos"));
	FirstSpawnPosition->SetupAttachment(SpawnPositions);

	SecondSpawnPosition = CreateDefaultSubobject<USceneComponent>(TEXT("SecondPos"));
	SecondSpawnPosition->SetupAttachment(SpawnPositions);

	ThirdSpawnPosition = CreateDefaultSubobject<USceneComponent>(TEXT("ThirdPos"));
	ThirdSpawnPosition->SetupAttachment(SpawnPositions);

	FourthSpawnPosition = CreateDefaultSubobject<USceneComponent>(TEXT("FourthPos"));
	FourthSpawnPosition->SetupAttachment(SpawnPositions);

	PortalSpawnPosition = CreateDefaultSubobject<USceneComponent>(TEXT("RewardPos"));
	PortalSpawnPosition->SetupAttachment(SpawnPositions);

	TurnNumbers = 3;
}

// Called when the game starts or when spawned
void ARoomKiller::BeginPlay(){

	Super::BeginPlay();
	
	//Spawn the enemies spawners.
	Spawners.Add(GetWorld()->SpawnActor<AActorSpawner>(SpawnerClass,FirstSpawnPosition->GetComponentLocation(),
		FirstSpawnPosition->GetComponentRotation()));

	Spawners.Add(GetWorld()->SpawnActor<AActorSpawner>(SpawnerClass,SecondSpawnPosition->GetComponentLocation(),
		SecondSpawnPosition->GetComponentRotation()));

	Spawners.Add(GetWorld()->SpawnActor<AActorSpawner>(SpawnerClass,ThirdSpawnPosition->GetComponentLocation(),
		ThirdSpawnPosition->GetComponentRotation()));
		
	Spawners.Add(GetWorld()->SpawnActor<AActorSpawner>(SpawnerClass,FourthSpawnPosition->GetComponentLocation(),
		FourthSpawnPosition->GetComponentRotation()));

	InteractiveActor = GetWorld()->SpawnActor<APawnInteractiveClass>(NpcClass,PortalSpawnPosition->GetComponentLocation() + FVector(0.f,0.f,+83.f),FRotator::ZeroRotator);
	InteractiveActor->LeftChoice.AddDynamic(this,&ARoomKiller::Start);
	InteractiveActor->EndDialog.AddDynamic(this,&ARoomKiller::ReStartNpc);

	//Select a speech.
    InteractiveActor->Speech = TArray<FString>{"You are going to fight some enemies in a battle royale with a number of rounds.", "-"};

    //Creation of NPC conversation parameter.
    FQuestion Question; 

    Question.Question = "Are you ready?";
    Question.Answers.Add("Yes");
    Question.Answers.Add("No");
    InteractiveActor->Questions.Add(Question);
	InteractiveActor->QuestionAt = 1;

	EndArena.AddDynamic(this, &ARoomKiller::OpenDoor);

}

// Called every frame
void ARoomKiller::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

	if(bStart){

		if(TurnNumbers > 0){
			
			if(CheckAllEnemyDeath()){
				for(AActorSpawner* Spawner: Spawners){
					
					if(ActorsToSpawn.Num() == 0){
						UE_LOG(LogTemp,Warning,TEXT("No Enemies selected"));
						return;
					}

					if(Spawner == nullptr){
						UE_LOG(LogTemp,Warning,TEXT("No Spawner selected"));
						return;
					}

					Spawner->ActorToSpawn = ActorsToSpawn[FMath::RandRange(0,ActorsToSpawn.Num() - 1)];

					//Memorize all the enemies to be eliminated to pass the round
					AEnemyAIAbstract* Enemy = Cast<AEnemyAIAbstract>(Spawner->SpawnActor());

					if(Enemy != nullptr){
				
						Enemies.Add(Enemy);
						Enemy->End.AddDynamic(this,&ARoomKiller::EndEnemies);
						Enemy->bNoIncrease = true;

					}
	
				}
			}

		}
		
		if(TurnNumbers == 0){
			
			if(CheckAllEnemyDeath())
				
				EndArena.Broadcast();

		}

	}

}

void ARoomKiller::Start() {
	
    InteractiveActor->Destroy();
	bStart = true;
}

void ARoomKiller::ReStartNpc(APawnInteractiveClass* SpokenActor) {
	
	InteractiveActor->QuestionAt = 1;

}

void ARoomKiller::EndEnemies(AEnemyAIAbstract* Enemy){

	Enemies.Remove(Enemy);

}

bool ARoomKiller::CheckAllEnemyDeath() {

    if(Enemies.Num() != 0)
		return false;

	TurnNumbers -= 1;

	return true;

}

void ARoomKiller::OpenDoor() {

    Door->bOpenDoor = true;

	FTransform Transform;
	Transform.SetLocation(PortalSpawnPosition->GetComponentLocation());
	Transform.SetRotation(FRotator::ZeroRotator.Quaternion());

	APortal* EndPortal = GetWorld()->SpawnActorDeferred<APortal>(PortalClass, Transform);
    EndPortal->NewPosition = StartPortalPos;
	EndPortal->FinishSpawning(Transform);
	
}


