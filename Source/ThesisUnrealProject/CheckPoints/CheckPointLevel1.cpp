// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckPointLevel1.h"
#include "../Character/CharacterPawnQuad.h"
#include "Kismet/GameplayStatics.h"
#include "../Elements/Maze/Maze.h"
#include "EngineUtils.h"
#include "../Elements/Destructible/GenericDestructibleElements.h"
#include "../Elements/GeneralElements/CoinController.h"
#include "../Elements/Hat/Hat.h"
#include "../Obstacle/Trap.h"
#include "../Elements/GeneralElements/Heart.h"
#include "../Elements/Platforms/ShakingFallenPlatform.h"
#include "../Elements/GeneralElements/Doors/Door.h"
#include "../GameManager/MazeManager.h"
#include "../Character/AllyAI/PawnInteractiveClass.h"
#include "../Character/AllyAI/PawnInteractiveMove.h"
#include "../Character/EnemyAI/PatrolAI2.h"

void ACheckPointLevel1::OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit) {

    if(OtherActor->IsA(ACharacterPawnQuad::StaticClass())){

        if (USaveGameLevel1* SaveGameInstance = Cast<USaveGameLevel1>(UGameplayStatics::CreateSaveGameObject(USaveGameLevel1::StaticClass()))){

            TArray<FGeneralActor> GeneralElem;
            TArray<FMoveActor> MoveElem;
            FTransform Transform;
            
// --- Maze Actor --

            TMap<int, FMazeValue> MazeTransformMap;
            int ActorNumber = 0;
            for (TActorIterator<AMaze> ActorItr(GetWorld()); ActorItr; ++ActorItr){
                
                //Fill up all the value
                FMazeValue T;
                T.TransformsFloor = CreateTransformArray((*ActorItr)->FloorInstances);
                T.TransformsWall = CreateTransformArray((*ActorItr)->WallInstances);
                T.TransformsObstacle = CreateTransformArray((*ActorItr)->ObstacleInstances);
                T.Position = ActorItr->GetActorLocation();

                MazeTransformMap.Add(ActorNumber,T);
                
                ActorNumber += 1;

            }


            SaveGameInstance->MazeTransformMap = MazeTransformMap;

// --- Destructible ---

        for (TActorIterator<AGenericDestructibleElements> ActorItr(GetWorld()); ActorItr; ++ActorItr){
            
            FGeneralActor GeneralActor;
            Transform.SetLocation(ActorItr->GetActorLocation());
            Transform.SetRotation(FRotator::ZeroRotator.Quaternion());
            GeneralActor.Transform = Transform;
            GeneralActor.ActorClass = ActorItr->GetClass();
            
            GeneralElem.Add(GeneralActor);

        }

        SaveGameInstance->DestructibleElem = GeneralElem;

// --- Coins ---

        GeneralElem.Empty();

        for (TActorIterator<ACoinController> ActorItr(GetWorld()); ActorItr; ++ActorItr){
            
            FGeneralActor GeneralActor;
            Transform.SetLocation(ActorItr->GetActorLocation());
            Transform.SetRotation(FRotator::ZeroRotator.Quaternion());
            GeneralActor.Transform = Transform;
            GeneralActor.ActorClass = ActorItr->GetClass();
            
            GeneralElem.Add(GeneralActor);

        }

        SaveGameInstance->CoinElem = GeneralElem;

// --- Hat ---
        
        GeneralElem.Empty();

        for (TActorIterator<AHat> ActorItr(GetWorld()); ActorItr; ++ActorItr){
            
            FGeneralActor GeneralActor;
            Transform.SetLocation(ActorItr->GetActorLocation());
            Transform.SetRotation(FRotator::ZeroRotator.Quaternion());
            GeneralActor.Transform = Transform;
            GeneralActor.ActorClass = ActorItr->GetClass();
            
            GeneralElem.Add(GeneralActor);

        }

        SaveGameInstance->HatElem = GeneralElem;

// --- Trap ---
        
        GeneralElem.Empty();

        for (TActorIterator<ATrap> ActorItr(GetWorld()); ActorItr; ++ActorItr){
            
            FGeneralActor GeneralActor;
            Transform.SetLocation(ActorItr->GetActorLocation());
            Transform.SetRotation(FRotator::ZeroRotator.Quaternion());
            GeneralActor.Transform = Transform;
            GeneralActor.ActorClass = ActorItr->GetClass();
            
            GeneralElem.Add(GeneralActor);

        }

        SaveGameInstance->TrapElem = GeneralElem;

// --- Heart ---
        
        GeneralElem.Empty();

        for (TActorIterator<AHeart> ActorItr(GetWorld()); ActorItr; ++ActorItr){
            
            FGeneralActor GeneralActor;
            Transform.SetLocation(ActorItr->GetActorLocation());
            Transform.SetRotation(FRotator::ZeroRotator.Quaternion());
            GeneralActor.Transform = Transform;
            GeneralActor.ActorClass = ActorItr->GetClass();
            
            GeneralElem.Add(GeneralActor);

        }

        SaveGameInstance->HeartElem = GeneralElem;

// --- Fallen Platforms ---
        
        GeneralElem.Empty();

        for (TActorIterator<AShakingFallenPlatform> ActorItr(GetWorld()); ActorItr; ++ActorItr){
            
            FGeneralActor GeneralActor;
            Transform.SetLocation(ActorItr->GetActorLocation());
            Transform.SetRotation(FRotator::ZeroRotator.Quaternion());
            GeneralActor.Transform = Transform;
            GeneralActor.ActorClass = ActorItr->GetClass();
            
            GeneralElem.Add(GeneralActor);

        }

        SaveGameInstance->FallenPlatformElem = GeneralElem;

// --- Doors ---

        GeneralElem.Empty();

        for (TActorIterator<ADoor> ActorItr(GetWorld()); ActorItr; ++ActorItr){
            
            FGeneralActor GeneralActor;
            Transform.SetLocation(ActorItr->GetActorLocation());
            Transform.SetRotation(ActorItr->GetActorRotation().Quaternion());
            GeneralActor.Transform = Transform;
            GeneralActor.ActorClass = ActorItr->GetClass();
            
            GeneralElem.Add(GeneralActor);

        }

        SaveGameInstance->Doors = GeneralElem;

// --- Enemy ---
        
        GeneralElem.Empty();

        for (TActorIterator<AEnemyAIAbstract> ActorItr(GetWorld()); ActorItr; ++ActorItr){
            
            AActor* Parent = ActorItr->GetAttachParentActor();
            if(ActorItr->GetAttachParentActor() == nullptr){

                FGeneralActor GeneralActor;
                Transform.SetLocation(ActorItr->GetActorLocation() + FVector(0.f,0.f,20.f));
                Transform.SetRotation(ActorItr->GetActorRotation().Quaternion());
                GeneralActor.Transform = Transform;
                GeneralActor.ActorClass = ActorItr->GetClass();
                
                GeneralElem.Add(GeneralActor);

            }

        }

        SaveGameInstance->Enemies = GeneralElem;

// --- Allies NPC ---
        
        GeneralElem.Empty();

        for (TActorIterator<APawnInteractiveClass> ActorItr(GetWorld()); ActorItr; ++ActorItr){
            
            AActor* Parent = ActorItr->GetAttachParentActor();
            if(ActorItr->GetAttachParentActor() == nullptr && !ActorItr->IsA(APawnInteractiveMove::StaticClass())){
            
                FGeneralActor GeneralActor;
                Transform.SetLocation(ActorItr->GetActorLocation() + FVector(0.f,0.f,20.f));
                Transform.SetRotation(ActorItr->GetActorRotation().Quaternion());
                GeneralActor.Transform = Transform;
                GeneralActor.ActorClass = ActorItr->GetClass();
                
                GeneralElem.Add(GeneralActor);
            
            }


        }

        SaveGameInstance->Allies = GeneralElem;

// --- Patrols NPC ---
        
        MoveElem.Empty();

        for (TActorIterator<APatrolAI2> ActorItr(GetWorld()); ActorItr; ++ActorItr){
            
            AActor* Parent = ActorItr->GetAttachParentActor();
            if(ActorItr->GetAttachParentActor() == nullptr){
                
                FMoveActor MoveActor;
                Transform.SetLocation((*ActorItr)->Positions[(*ActorItr)->StartIndex]);
                Transform.SetRotation(ActorItr->GetActorRotation().Quaternion());
                MoveActor.Transform = Transform;
                MoveActor.ActorClass = ActorItr->GetClass();
                MoveActor.Positions = (*ActorItr)->Positions;
                MoveActor.StartIndex = (*ActorItr)->StartIndex;
                MoveActor.StartDirection = (*ActorItr)->StartDirection;
                
                MoveElem.Add(MoveActor);
            
            }

        }

        SaveGameInstance->Patrols = MoveElem;

// --- Move Ally ---

        MoveElem.Empty();

        for (TActorIterator<APawnInteractiveMove> ActorItr(GetWorld()); ActorItr; ++ActorItr){
            
            AActor* Parent = ActorItr->GetAttachParentActor();
            if(ActorItr->GetAttachParentActor() == nullptr){
                
                FMoveActor MoveActor;
                Transform.SetLocation(ActorItr->GetActorLocation());
                Transform.SetRotation(ActorItr->GetActorRotation().Quaternion());
                MoveActor.Transform = Transform;
                MoveActor.ActorClass = ActorItr->GetClass();
                MoveActor.Positions = (*ActorItr)->Positions;
                
                MoveElem.Add(MoveActor);
            
            }

        }

        SaveGameInstance->MoveAllies = MoveElem;

// --- Speech ---

        SaveGameInstance->Speech = CreateSpeech(MazeManager->Speech);
        SaveGameInstance->Questions = CreateSpeech(MazeManager->Questions);
        SaveGameInstance->BlockedSpeech = CreateSpeech(MazeManager->BlockedSpeech);
        SaveGameInstance->OldSpeech = CreateSpeech(MazeManager->OldSpeech);
        SaveGameInstance->OldQuestions = CreateSpeech(MazeManager->OldQuestions);
        SaveGameInstance->OldBlockedSpeech = CreateSpeech(MazeManager->OldBlockedSpeech);

        // Start async save process.;
		UGameplayStatics::AsyncSaveGameToSlot(SaveGameInstance, "CheckpointLevel1", 0);

        }

    } 

}

//Create an array with the trasfomr of instanced mesh from the maze.
TArray<FTransform> ACheckPointLevel1::CreateTransformArray(UInstancedStaticMeshComponent* MeshInstances) {

    TArray<FTransform> Instance;
    for(int i = 0; i < MeshInstances->GetInstanceCount(); i++){

        FTransform Transform;
        MeshInstances->GetInstanceTransform(i,Transform);
        Instance.Add(Transform);

    } 
    
    return Instance;

}

//Convert an Array<Array<FString>> to TArray<FSpeech> (Nested loop are not permitted)
TArray<FSpeech> ACheckPointLevel1::CreateSpeech(TArray<TArray<FString>> List) {

    TArray<FSpeech> StringArray;
    for(int i = 0; i < List.Num(); i++){

        FSpeech Speech;
        Speech.String =  List[i];
        StringArray.Add(Speech);

    }

    return StringArray;

}