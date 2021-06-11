// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacterPawnQuad.h"
#include "EnemyAIAbstract.h"
#include "Components/BoxComponent.h"
#include "AIController.h"
#include "Kismet/KismetSystemLibrary.h"

AAICharacterPawnQuad::AAICharacterPawnQuad() {
    
    EnemyInRangeTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerInRange"));
    EnemyInRangeTrigger->SetupAttachment(RootComponent);

}

void AAICharacterPawnQuad::BeginPlay() {

    Super::BeginPlay();

}

void AAICharacterPawnQuad::Tick(float DeltaTime) {
    
    Super::Tick(DeltaTime);

    EnemyInRangeTrigger->GetOverlappingActors(UnSortedEnemies,AEnemyAIAbstract::StaticClass());
    
    UnSortedEnemies.Sort( 
        [this](const AActor& FirstElem, const AActor& SecondElem)  {
         return (FirstElem.GetActorLocation() - this->GetActorLocation()).Size() > 
            (SecondElem.GetActorLocation() - this->GetActorLocation()).Size();  
    });

    Enemies = UnSortedEnemies;

    //for(AEnemyAIAbstract* Enemy: Enemies)
    //    UE_LOG(LogTemp,Warning,TEXT(" %s : %f "), *Enemy->GetName(), (Enemy->GetActorLocation() - this->GetActorLocation()).Size());

}

//This pawn is invulnerable.
float AAICharacterPawnQuad::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) {
    return 0;
}

void AAICharacterPawnQuad::OnBeginTriggerOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit) {
    
    if(OtherActor->IsA(AEnemyAIAbstract::StaticClass()) && OtherActor != this){
        
        AController* MyController = Cast<AEnemyAIAbstract>(OtherActor)->GetController();
        if(MyController == nullptr ||  MyController->IsA(APlayerController::StaticClass()))
            return;

        Enemies.Add(Cast<AEnemyAIAbstract>(OtherActor));

    }

}

void AAICharacterPawnQuad::OnEndTriggerOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
    if(OtherActor->IsA(AEnemyAIAbstract::StaticClass()) && !OtherActor->IsA(this->StaticClass())){

        AController* MyController = Cast<AEnemyAIAbstract>(OtherActor)->GetController();

        Enemies.Remove(Cast<AEnemyAIAbstract>(OtherActor));

    }
    
}

