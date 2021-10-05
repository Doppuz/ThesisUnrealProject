// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorExplorer.h"
#include "../../Puzzle/PuzzleButton.h"


ADoorExplorer::ADoorExplorer() {

    SpawnPos1 = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPos1"));
	SpawnPos1->SetupAttachment(RootComponent);

    SpawnPos2 = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPos2"));
	SpawnPos2->SetupAttachment(RootComponent);

    SpawnPos3 = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPos3"));
	SpawnPos3->SetupAttachment(RootComponent);
    
}

void ADoorExplorer::BeginPlay() {

    Super::BeginPlay();

    PuzzleActors.Add(GetWorld()->SpawnActor<APuzzleButton>(PuzzleClass,SpawnPos1->GetComponentLocation(),SpawnPos1->GetComponentRotation()));
    PuzzleActors.Add(GetWorld()->SpawnActor<APuzzleButton>(PuzzleClass,SpawnPos2->GetComponentLocation(),SpawnPos2->GetComponentRotation()));
    PuzzleActors.Add(GetWorld()->SpawnActor<APuzzleButton>(PuzzleClass,SpawnPos3->GetComponentLocation(),SpawnPos3->GetComponentRotation()));
     
    FAttachmentTransformRules TransformRules(EAttachmentRule::KeepWorld,true);
    for(int i = 0; i < PuzzleActors.Num(); i++){
        
        PuzzleActors[i]->Overlap.AddDynamic(this, &ADoorExplorer::PuzzleOverlap);
        PuzzleActors[i]->AttachToActor(this,TransformRules);
    
    }

    Shuffle();

}

void ADoorExplorer::Shuffle() {
    
    for(int i = PuzzleActors.Num() - 1; i > 0; i--){

        int ExtrNum = FMath::RandRange(0,i);
        APuzzleButton* Temp = PuzzleActors[i];
        PuzzleActors[i] = PuzzleActors[ExtrNum];
        PuzzleActors[ExtrNum] = Temp;

    }

}

void ADoorExplorer::PuzzleOverlap(APuzzleButton* Elem) {
    
    MyPuzzleOrder.Add(Elem);

    if(MyPuzzleOrder.Num() == PuzzleActors.Num()){

        for(int i = 0; i < MyPuzzleOrder.Num(); i++){

            if(MyPuzzleOrder[i] != PuzzleActors[i]){
                
                MyPuzzleOrder.Empty();

                for(int j = 0; j < PuzzleActors.Num(); j++){
                    PuzzleActors[j]->Mesh->SetMaterial(0, RedColor);
                }
                
                GetWorld()->GetTimerManager().SetTimer(ResetPuzzleTimer,this,& ADoorExplorer::ResetPuzzle,0.5f,false);

                return;

            }


        }

        OpenDoor();
    
    }

}

void ADoorExplorer::ResetPuzzle() {
    
    for(APuzzleButton* Button : PuzzleActors){
		Button->Mesh->SetMaterial(0,nullptr);	
    	Button->bDisableOverlap = false;
	}

}