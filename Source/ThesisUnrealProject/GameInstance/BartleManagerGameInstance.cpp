// Fill out your copyright notice in the Description page of Project Settings.


#include "BartleManagerGameInstance.h"

UBartleManagerGameInstance::UBartleManagerGameInstance() {
    
    IncreaseValue = 50.f / 6.f;

    Types.Add(Type::Achiever, 50.f);
    Types.Add(Type::Killer, 50.f);
    Types.Add(Type::Socializer, 50.f);
    Types.Add(Type::Explorer, 50.f);

    TypesQuestionary.Add(Type::Achiever, 50.f);
    TypesQuestionary.Add(Type::Killer, 50.f);
    TypesQuestionary.Add(Type::Socializer, 50.f);
    TypesQuestionary.Add(Type::Explorer, 50.f);

}

//Change these value in an equally distributed way. (-1 means that I don't want to touch that value).
void UBartleManagerGameInstance::EquallyDistributedUpdate(Type IncreasedType,float IncreasedValue,Type DecreasedType,float DecreasedValue) {
    

    if(IncreasedType != -1)
        Types[IncreasedType] += IncreasedValue;

    if(DecreasedType != -1)
        Types[DecreasedType] -= DecreasedValue;


    UE_LOG(LogTemp,Warning,TEXT(""));
    UE_LOG(LogTemp,Warning,TEXT("-------------"));

    UE_LOG(LogTemp,Warning,TEXT(" Achiever: %f"), Types[Type::Achiever]);
    UE_LOG(LogTemp,Warning,TEXT(" Killer: %f"), Types[Type::Killer]);
    UE_LOG(LogTemp,Warning,TEXT(" Explorer: %f"), Types[Type::Explorer]);
    UE_LOG(LogTemp,Warning,TEXT(" Socializer: %f"), Types[Type::Socializer]);
}

void UBartleManagerGameInstance::EquallyDistributedUpdate(Type IncreasedType, Type DecreasedType) {

    if(IncreasedType != -1)
        Types[IncreasedType] += IncreaseValue;

    if(DecreasedType != -1)
        Types[DecreasedType] -= IncreaseValue;


    UE_LOG(LogTemp,Warning,TEXT(""));
    UE_LOG(LogTemp,Warning,TEXT("-------------"));

    UE_LOG(LogTemp,Warning,TEXT(" Achiever: %f"), Types[Type::Achiever]);
    UE_LOG(LogTemp,Warning,TEXT(" Killer: %f"), Types[Type::Killer]);
    UE_LOG(LogTemp,Warning,TEXT(" Explorer: %f"), Types[Type::Explorer]);
    UE_LOG(LogTemp,Warning,TEXT(" Socializer: %f"), Types[Type::Socializer]);
}

void UBartleManagerGameInstance::DistributedUpdate(Type IncreasedType, Type DecreasedType) {
    

    /*if((*Map)[IncreasedType] < (*Map)[DecreasedType]){
    
        if(IncreasedType != -1)
            (*Map)[IncreasedType] += (IncreaseValue + IncreaseValue / 2);

        if(DecreasedType != -1)
            (*Map)[DecreasedType] -= IncreaseValue / 2 ;

    }else if ((*Map)[IncreasedType] > (*Map)[DecreasedType]){
        
        if(IncreasedType != -1)
            (*Map)[IncreasedType] += IncreaseValue / 2;

        if(DecreasedType != -1)
            (*Map)[DecreasedType] -= (IncreaseValue + IncreaseValue / 2);

    }else{
        EquallyDistributedUpdate(IncreasedType, DecreasedType);
        return;
    }*/

    if(IncreasedType != -1)
        Types[IncreasedType] += IncreaseValue;

    if(DecreasedType != -1)
        Types[DecreasedType] -= IncreaseValue;

    UE_LOG(LogTemp,Warning,TEXT(""));
    UE_LOG(LogTemp,Warning,TEXT("-------------"));

    UE_LOG(LogTemp,Warning,TEXT(" Achiever: %f"), Types[Type::Achiever]);
    UE_LOG(LogTemp,Warning,TEXT(" Killer: %f"), Types[Type::Killer]);
    UE_LOG(LogTemp,Warning,TEXT(" Explorer: %f"), Types[Type::Explorer]);
    UE_LOG(LogTemp,Warning,TEXT(" Socializer: %f"), Types[Type::Socializer]);
}

TMap<Type,float> UBartleManagerGameInstance::GetBartleTypes() {
    
    return Types;

}

void UBartleManagerGameInstance::ResetValue() {
    Types[Type::Achiever] = 50;
    Types[Type::Explorer] = 50;
    Types[Type::Socializer] = 50;
    Types[Type::Killer] = 50;
}
