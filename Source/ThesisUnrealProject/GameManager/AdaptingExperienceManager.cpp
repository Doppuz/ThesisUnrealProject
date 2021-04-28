// Fill out your copyright notice in the Description page of Project Settings.


#include "AdaptingExperienceManager.h"


AdaptingExperienceManager::AdaptingExperienceManager(float* Achiever, float* Killer, float* Socializer, float* Explorer) {
    Types.Add(Type::Achiever, Achiever);
    Types.Add(Type::Killer, Killer);
    Types.Add(Type::Socializer, Socializer);
    Types.Add(Type::Explorer, Explorer);
}

AdaptingExperienceManager::~AdaptingExperienceManager(){
}

void AdaptingExperienceManager::WeightUpdate(Type IncreaseType, float Value, TArray<Type> DecreasedTypes) {
    
    /*(*Types[IncreaseType]) += Value;
    
    TMap<Type,float*> Temp = Types;



    Types.ValueSort([](float A, float B){
        return A < B;
    });
    
    for(int i = 0; i < DecreasedTypes.Num(); i++){

    }*/

}

void AdaptingExperienceManager::EquallyDistributedUpdate(Type IncreaseType, float Value, TArray<Type> DecreasedTypes) {
    (*Types[IncreaseType]) += Value;
    for(Type DecType: DecreasedTypes)
        (*Types[DecType]) -= Value/DecreasedTypes.Num();
}

