// Fill out your copyright notice in the Description page of Project Settings.


#include "RiddleArena.h"
#include "../../../../GameManager/MazeCell2.h"
#include "../../../../GameManager/MazeManager.h"
#include "../../Elements/RiddleAndDoor.h"
#include "../../../GeneralElements/Door.h"
#include "../../../../Character/AllyAI/RiddleNPC.h"
#include "../../../../Character/AllyAI/PawnInteractiveClass.h"
#include "Misc/FileHelper.h"
#include "Kismet/KismetArrayLibrary.h"

void ARiddleArena::BeginPlay() {
    
    Super::BeginPlay();

}

void ARiddleArena::LoadFromFile(TArray<TArray<FString>>& List, FString FileName) {

    TArray<FString> StringArray;
    FString CompleteFilePath = FPaths::GameSourceDir() + "ThesisUnrealProject/TextFiles/" + FileName +".txt"; 
    FFileHelper::LoadFileToStringArray(StringArray,*CompleteFilePath);

    for(FString String : StringArray){
        
        TArray<FString> Result;
        String.ParseIntoArray(Result, _T(","),true);
        List.Add(Result);

    }

   
    
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

            //Subtraction between the current cell and the next one;
            float Subtraction = FMath::Abs(MaxPath[i]->GetActorLocation().X - MaxPath[i+1]->GetActorLocation().X);

            if(Subtraction > 0.1f)
                NewDoor->SetActorRotation(FRotator(0.f,90.f,0.f));

            //NPC spawn.
            ARiddleNPC* NPC = GetWorld()->SpawnActor<ARiddleNPC>(RiddleNpcClass,MaxPath[i]->GetActorLocation(),FRotator::ZeroRotator);     
	        int SpeechNumber = FMath::RandRange(0,(*Speech).Num() - 1);
            NPC->Speech = (*Speech)[SpeechNumber];

            //Creation of NPC conversation parameter.
            FQuestion Question; 
            
            //I always randomize the questions, if they end, I reload every question from the beginning.
            if((*Questions).Num() < 1){
            
                (*Questions) = (*OldQuestions);
                (*OldQuestions).Empty();
            
            }

            //Select a random question.
            int QuestionNumber = FMath::RandRange(0,(*Questions).Num() - 1);
            //The first element is the question, instead the other 4 are the answers.
            Question.Question = (*Questions)[QuestionNumber][0];
            (*OldQuestions).Add((*Questions)[QuestionNumber]);
            (*Questions)[QuestionNumber].RemoveAt(0);
            
            NPC->RightAnswerPos = ShuffleArray((*Questions)[QuestionNumber]);
            
            Question.Answers = (*Questions)[QuestionNumber];
            (*Questions).RemoveAt(QuestionNumber);

            NPC->Questions.Add(Question);
            NPC->ConnectedDoor = NewDoor;
            NPC->Solved.AddDynamic(this,&ARiddleArena::OpenRiddleDoor);
            NPC->EndDialog.AddDynamic(this,&ARiddleArena::EndDialog);

        }

        Contator += 1;

        if(i == MaxPath.Num() - 1)
            GetWorld()->SpawnActor<APawnInteractiveClass>(SpokenNpcClass,MaxPath[i]->GetActorLocation(),FRotator::ZeroRotator);

    }

}

void ARiddleArena::OpenRiddleDoor(ARiddleNPC* RiddleActor) {
    
    RiddleActor->ConnectedDoor->bOpenDoor = true;

}

void ARiddleArena::EndDialog(APawnInteractiveClass* SpokenActor) {

    if(!Cast<ARiddleNPC>(SpokenActor)->ConnectedDoor->bOpenDoor){
	
    	Cast<ARiddleNPC>(SpokenActor)->QuestionAt = 200; 

        //Change the questoin every time I answer incorrectly.

        FQuestion Question; 
            
        if((*Questions).Num() < 1){
            
            (*Questions) = (*OldQuestions);
            (*OldQuestions).Empty();
            
        }

        int QuestionNumber = FMath::RandRange(0,(*Questions).Num() - 1);
        Question.Question = (*Questions)[QuestionNumber][0];
        (*OldQuestions).Add((*Questions)[QuestionNumber]);
        (*Questions)[QuestionNumber].RemoveAt(0);
        Question.Answers = (*Questions)[QuestionNumber];
        
        Cast<ARiddleNPC>(SpokenActor)->RightAnswerPos = ShuffleArray((*Questions)[QuestionNumber]);
            
        Question.Answers = (*Questions)[QuestionNumber];
        (*Questions).RemoveAt(QuestionNumber);

        SpokenActor->Questions.RemoveAt(0);
        SpokenActor->Questions.Add(Question);
    
    }
    
}

int ARiddleArena::ShuffleArray(TArray<FString>& ShuffledArray) {

    int CorrectAnswerPos = 0;
    
    for(int i = ShuffledArray.Num() - 1; i > 0; i--){

        int ExtrNum = FMath::RandRange(0,i);
        FString Temp = ShuffledArray[i];
        ShuffledArray[i] = ShuffledArray[ExtrNum];
        ShuffledArray[ExtrNum] = Temp;

        if(ExtrNum == CorrectAnswerPos)
            CorrectAnswerPos = i;

    }

    return CorrectAnswerPos;

}