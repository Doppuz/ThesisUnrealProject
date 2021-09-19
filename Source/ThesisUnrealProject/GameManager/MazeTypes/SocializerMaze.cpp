// Fill out your copyright notice in the Description page of Project Settings.


#include "SocializerMaze.h"
#include "../../GameManager/MazeCell2.h"
#include "../../GameManager/MazeManager.h"
#include "../../Elements/GeneralElements/Doors/Door.h"
#include "../../Character/AllyAI/RiddleNPC.h"
#include "../../Character/AllyAI/PawnInteractiveClass.h"
#include "Misc/FileHelper.h"
#include "Kismet/KismetArrayLibrary.h"
#include "Components/BoxComponent.h"
#include "../../Elements/Portal/Portal.h"	
#include "../../Elements/GeneralElements/Doors/DoorRiddle.h"
#include "../../Elements/Maze/Maze.h"


ASocializerMaze::ASocializerMaze() {
    
    PopulateMaze = false;

}

void ASocializerMaze::GenerateRiddleDoors() {

    FTransform Transform;
    int Contator = 0;
    
    for(int i = 1; i < MaxPath.Num(); i += 4){

            Contator = 0;

            Transform.SetLocation((MaxPath[i]->GetActorLocation() + MaxPath[i + 1]->GetActorLocation())/2);
            Transform.SetRotation(GetDoorRotation(i).Quaternion());
            ADoorRiddle* Door = GetWorld()->SpawnActorDeferred<ADoorRiddle>(DoorRiddleClass,Transform);
            Door->Speech = &Speech;
            Door->OldSpeech = &OldSpeech;
            Door->Questions = &Questions;
            Door->OldQuestions = &OldQuestions;
            Door->FinishSpawning(Transform);

            FAttachmentTransformRules TransformRules(EAttachmentRule::KeepWorld,true);
            Door->AttachToActor(MazeActor,TransformRules);

            if(i + 4 >= MaxPath.Num() - 1){
                Door->NPC->Solved.AddDynamic(this,&ASocializerMaze::OpenDoor);
            }

    }
     

    //Generate allies in the last cells of each other paths.
    
    for(Graph<TArray<AMazeCell2*>> Grp : OtherPaths){

        TArray<TArray<AMazeCell2*>*> Leaves = Grp.GetLeaves();

        for(TArray<AMazeCell2*>* Cells: Leaves){

            if(!(*Cells)[Cells->Num() - 1]->bIsRoom){
                APawnInteractiveClass* NPC = GetWorld()->SpawnActor<APawnInteractiveClass>(SpokenNpcClass,(*Cells)[Cells->Num() - 1]->GetActorLocation(),FRotator::ZeroRotator);
                
                if(BlockedSpeech.Num() == 0){

                    BlockedSpeech = OldBlockedSpeech;
                    OldBlockedSpeech.Empty();
                
                }

                int SpeechNumber = FMath::RandRange(0,BlockedSpeech.Num() - 1);
                
                NPC->Speech = BlockedSpeech[SpeechNumber];
                OldBlockedSpeech.Add(BlockedSpeech[SpeechNumber]);
                BlockedSpeech.RemoveAt(SpeechNumber);

                
                FAttachmentTransformRules TransformRules(EAttachmentRule::KeepWorld,true);
                NPC->AttachToActor(MazeActor,TransformRules);
            }
        
        }

    }

}

void ASocializerMaze::OpenDoor(ARiddleNPC* RiddleActor) {
    
    if(ExternalDoor != nullptr)
        ExternalDoor->bOpenDoor = true;
    else
        UE_LOG(LogTemp,Warning, TEXT("No Door in SocializerMaze"));

    FTransform Transform;
	Transform.SetLocation(MaxPath[MaxPath.Num() - 1]->GetActorLocation());
	Transform.SetRotation(FRotator::ZeroRotator.Quaternion());

	APortal* EndPortal = GetWorld()->SpawnActorDeferred<APortal>(PortalClass, Transform);
    EndPortal->NewPosition = StartPortalPos;
	EndPortal->FinishSpawning(Transform);

}

void ASocializerMaze::BeginPlay() {

    Super::BeginPlay();

    GenerateRiddleDoors();
    
}

