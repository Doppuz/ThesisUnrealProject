// Fill out your copyright notice in the Description page of Project Settings.


#include "StatueInteractElem.h"

int AStatueInteractElem::ID = 0;

AStatueInteractElem::AStatueInteractElem() {
    
    bFocus = false;

}

void AStatueInteractElem::BeginPlay(){

    Super::BeginPlay();

    TArray<FString> Text {"Statue #"+FString::FromInt(AStatueInteractElem::ID),"(I should find the others)"};
    Speech = Text;

    AStatueInteractElem::ID += 1;

}