// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorRiddle.h"
#include "../../../Character/AllyAI/RiddleNPC.h"

ADoorRiddle::ADoorRiddle() {

    SpawnPos1 = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPos1"));
	SpawnPos1->SetupAttachment(RootComponent);

}

void ADoorRiddle::BeginPlay() {

    Super::BeginPlay();

    ARiddleNPC* NPC = GetWorld()->SpawnActor<ARiddleNPC>( RiddleNpcClass, SpawnPos1->GetComponentLocation(), SpawnPos1->GetComponentRotation());
    NPC->Solved.AddDynamic(this,&ADoorRiddle::OpenDoor);
    
    //Select a speech.
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

}

int ADoorRiddle::ShuffleArray(TArray<FString>& ShuffledArray) {
    
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

void ADoorRiddle::OpenDoor(ARiddleNPC* RiddleActor) {
    
    bOpenDoor = true;

}
