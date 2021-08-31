// Fill out your copyright notice in the Description page of Project Settings.


#include "RiddleArena.h"
#include "../../../../GameManager/MazeCell2.h"
#include "../../../../GameManager/MazeManager.h"
#include "../../Elements/RiddleAndDoor.h"
#include "../../../GeneralElements/Door.h"
#include "../../../../Character/AllyAI/RiddleNPC.h"

void ARiddleArena::BeginPlay() {
    
    Super::BeginPlay();

}

void ARiddleArena::GenerateRiddleDoors() {

    TArray<AMazeCell2*> MaxPath = MazeManager->MaxPath;
    int Contator = 0;
    
    for(int i = 1; i < MaxPath.Num(); i++){

        if(Contator % 3 == 0 && i != MaxPath.Num() - 1){

            Contator = 0;

            FVector Pos = (MaxPath[i]->GetActorLocation() + MaxPath[i+1]->GetActorLocation())/2;
            Pos.Z += 200.f;
            ADoor* NewDoor = GetWorld()->SpawnActor<ADoor>(DoorClass,Pos,FRotator::ZeroRotator);
            NewDoor->SetActorScale3D(FVector(1.75f,1.f,0.75f));

            if(MaxPath[i]->GetActorLocation().X != MaxPath[i+1]->GetActorLocation().X)
                NewDoor->SetActorRotation(FRotator(0.f,90.f,0.f));

            ARiddleNPC* NPC = GetWorld()->SpawnActor<ARiddleNPC>(RiddleNpcClass,MaxPath[i]->GetActorLocation(),FRotator::ZeroRotator);     
	        NPC->Speech.Add("daadsa");
            NPC->Speech.Add("f");
            NPC->Speech.Add("g");
            NPC->Speech.Add("t");
            NPC->QuestionAt = 1;
            FQuestion Question;
            Question.Question = "Lalalala";
            Question.Answers = TArray<FString>{"eads","e","ds","v"};
            NPC->Questions.Add(Question);
            NPC->RightAnswerPos = 0;
            NPC->ConnectedDoor = NewDoor;
            NPC->Solved.AddDynamic(this,&ARiddleArena::OpenRiddleDoor);
            NPC->EndDialog.AddDynamic(this,&ARiddleArena::EndDialog);

        }

        Contator += 1;

    }

}

void ARiddleArena::OpenRiddleDoor(ARiddleNPC* RiddleActor) {
    
    RiddleActor->ConnectedDoor->bOpenDoor = true;

}

void ARiddleArena::EndDialog(APawnInteractiveClass* SpokenActor) {

    if(!Cast<ARiddleNPC>(SpokenActor)->ConnectedDoor->bOpenDoor)
		Cast<ARiddleNPC>(SpokenActor)->QuestionAt = 1;
    
}
