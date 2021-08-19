// Fill out your copyright notice in the Description page of Project Settings.


#include "Trigger.h"
#include "Components/BoxComponent.h"
#include "../../Projectile/SquaredProjectile.h"
#include "../../Character/CharacterPawnQuad.h"
#include "../../AI/Controller/QuadAIControllerStationary.h"
#include "../../Character/EnemyAI/PatrolAIPawn.h"

// Sets default values
ATrigger::ATrigger(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Trigger->SetupAttachment(RootComponent);

	bBlockVisibility = false;
}


// Called when the game starts or when spawned
void ATrigger::BeginPlay(){
	
	Super::BeginPlay();
	
	TypeOfOverlap();

	ChangeVisibility(bBlockVisibility);

}

// Called every frame
void ATrigger::Tick(float DeltaTime){
	
	Super::Tick(DeltaTime);

}

void ATrigger::OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit) {

	if(OtherActor->IsA(ASquaredProjectile::StaticClass()))
		OtherActor->Destroy();
	else if(OtherActor->IsA(ACharacterPawnQuad::StaticClass())){
		ACharacterPawnQuad* MyPawn = Cast<ACharacterPawnQuad>(OtherActor);
		if(MyPawn->GetController()->IsA(AQuadAIControllerStationary::StaticClass())){
			AQuadAIControllerStationary* Controller = Cast<AQuadAIControllerStationary>(MyPawn->GetController());
			Controller->MovementValue = -Controller->MovementValue;
		}
	}

}

void ATrigger::ChangeVisibility(bool Visibility) {
	
	if(Visibility)
		Trigger->SetCollisionProfileName(TEXT("TriggerWallNoVisibility"));
	else
		Trigger->SetCollisionProfileName(TEXT("TriggerWall"));


}

void ATrigger::TypeOfOverlap() {
	
	Trigger->OnComponentBeginOverlap.AddDynamic(this,&ATrigger::OnOverlap);

}
