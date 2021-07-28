// Fill out your copyright notice in the Description page of Project Settings.


#include "AdaptiveExperience.h"

AdaptiveExperience::AdaptiveExperience(){

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

AdaptiveExperience::~AdaptiveExperience()
{
}

//Change these value in an equally distributed way. (-1 means that I don't want to touch that value).
void AdaptiveExperience::EquallyDistributedUpdate(Type IncreasedType,float IncreasedValue,Type DecreasedType,float DecreasedValue) {
    
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

void AdaptiveExperience::EquallyDistributedUpdate(Type IncreasedType, Type DecreasedType) {

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

void AdaptiveExperience::DistributedUpdate(Type IncreasedType, Type DecreasedType) {
    

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

TMap<Type,float> AdaptiveExperience::GetBartleTypes() {
    
    return Types;

}

void AdaptiveExperience::ResetValue() {
    Types[Type::Achiever] = 50;
    Types[Type::Explorer] = 50;
    Types[Type::Socializer] = 50;
    Types[Type::Killer] = 50;
}

void AdaptiveExperience::SaveFile(FString) {
    FString file = FPaths::ProjectDir();
    file.Append(TEXT("Result.txt"));

    // We will use this FileManager to deal with the file.
    IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile();

    FString StringToWrite = "Achiever: "+FString::SanitizeFloat(Types[Type::Achiever]) + 
                        " Explorer: "+FString::SanitizeFloat(Types[Type::Explorer])+
                        " Killer: "+FString::SanitizeFloat(Types[Type::Killer])+
                        " Socializer: "+FString::SanitizeFloat(Types[Type::Socializer])+
                        " ----------- AchieverQ: "+FString::SanitizeFloat(TypesQuestionary[Type::Achiever])+
                        " ExplorerQ: "+FString::SanitizeFloat(TypesQuestionary[Type::Explorer])+
                        " KillerQ: "+FString::SanitizeFloat(TypesQuestionary[Type::Killer])+
                        " SocializerQ: "+FString::SanitizeFloat(TypesQuestionary[Type::Socializer])+" \n";

        // We use the LoadFileToString to load the file into
        if(FFileHelper::SaveStringToFile(StringToWrite,*file, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Append)){
            UE_LOG(LogTemp, Warning, TEXT("AA \"%s\""),*file);
        }else{
            UE_LOG(LogTemp, Warning, TEXT("FileManipulation: Failed to write FString to file."));
        }

}

void AdaptiveExperience::LoadFile(FString) {
    
}
