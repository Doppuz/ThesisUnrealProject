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
#include "../Elements/Platforms/ShakingFallenPlatform.h"

void ACheckPointLevel1::OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit) {

    if(OtherActor->IsA(ACharacterPawnQuad::StaticClass())){

        if (USaveGameLevel1* SaveGameInstance = Cast<USaveGameLevel1>(UGameplayStatics::CreateSaveGameObject(USaveGameLevel1::StaticClass()))){

            TArray<FGeneralActor> GeneralElem;
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
            GeneralActor.Position = ActorItr->GetActorLocation();
            GeneralActor.ActorClass = ActorItr->GetClass();
            
            GeneralElem.Add(GeneralActor);

        }

        SaveGameInstance->DestructibleElem = GeneralElem;

// --- Coins ---

        GeneralElem.Empty();

        for (TActorIterator<ACoinController> ActorItr(GetWorld()); ActorItr; ++ActorItr){
            
            FGeneralActor GeneralActor;
            GeneralActor.Position = ActorItr->GetActorLocation();
            GeneralActor.ActorClass = ActorItr->GetClass();
            
            GeneralElem.Add(GeneralActor);

        }

        SaveGameInstance->CoinElem = GeneralElem;

// --- Hat ---
        
        GeneralElem.Empty();

        for (TActorIterator<AHat> ActorItr(GetWorld()); ActorItr; ++ActorItr){
            
            FGeneralActor GeneralActor;
            GeneralActor.Position = ActorItr->GetActorLocation();
            GeneralActor.ActorClass = ActorItr->GetClass();
            
            GeneralElem.Add(GeneralActor);

        }

        SaveGameInstance->HatElem = GeneralElem;

// --- Trap ---
        
        GeneralElem.Empty();

        for (TActorIterator<ATrap> ActorItr(GetWorld()); ActorItr; ++ActorItr){
            
            FGeneralActor GeneralActor;
            GeneralActor.Position = ActorItr->GetActorLocation();
            GeneralActor.ActorClass = ActorItr->GetClass();
            
            GeneralElem.Add(GeneralActor);

        }

        SaveGameInstance->TrapElem = GeneralElem;

// --- Heart ---
        
        GeneralElem.Empty();

        for (TActorIterator<ATrap> ActorItr(GetWorld()); ActorItr; ++ActorItr){
            
            FGeneralActor GeneralActor;
            GeneralActor.Position = ActorItr->GetActorLocation();
            GeneralActor.ActorClass = ActorItr->GetClass();
            
            GeneralElem.Add(GeneralActor);

        }

        SaveGameInstance->HeartElem = GeneralElem;

// --- Fallen Platforms ---
        
        GeneralElem.Empty();

        for (TActorIterator<AShakingFallenPlatform> ActorItr(GetWorld()); ActorItr; ++ActorItr){
            
            FGeneralActor GeneralActor;
            GeneralActor.Position = ActorItr->GetActorLocation();
            GeneralActor.ActorClass = ActorItr->GetClass();
            
            GeneralElem.Add(GeneralActor);

        }

        SaveGameInstance->FallenPlatformElem = GeneralElem;

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