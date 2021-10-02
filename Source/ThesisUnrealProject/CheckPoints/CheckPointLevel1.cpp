// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckPointLevel1.h"
#include "../Character/CharacterPawnQuad.h"
#include "SaveGameLevel1.h"
#include "Kismet/GameplayStatics.h"
#include "../Elements/Maze/Maze.h"
#include "EngineUtils.h"

void ACheckPointLevel1::OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit) {

    if(OtherActor->IsA(ACharacterPawnQuad::StaticClass())){

        if (USaveGameLevel1* SaveGameInstance = Cast<USaveGameLevel1>(UGameplayStatics::CreateSaveGameObject(USaveGameLevel1::StaticClass()))){

            TMap<int, FArrayTransform> MazeTransformMap;
            int ActorNumber = 0;
            for (TActorIterator<AMaze> ActorItr(GetWorld()); ActorItr; ++ActorItr){

                TArray<FTransform> FloorInstance;
                for(int i = 0; i < (*ActorItr)->FloorInstances->GetInstanceCount(); i++){

                    FTransform Transform;
                    (*ActorItr)->FloorInstances->GetInstanceTransform(i,Transform);
                    FloorInstance.Add(Transform);

                } 
                
                FArrayTransform T;
                T.Transforms = FloorInstance;

                MazeTransformMap.Add(ActorNumber,T);
                
                ActorNumber += 1;

            }


            SaveGameInstance->MazeTransformMap = MazeTransformMap;

            // Start async save process.
			UGameplayStatics::AsyncSaveGameToSlot(SaveGameInstance, "CheckpointLevel1", 0);

        }

    }
    
}
