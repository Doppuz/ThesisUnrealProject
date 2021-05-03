// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "Kismet/KismetMathLibrary.h"


UMyAnimInstance::UMyAnimInstance() {
    Speed = 0.f;
}

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds) {
    
    Super::NativeUpdateAnimation(DeltaSeconds);
    AActor* Own = GetOwningActor();

    if(Own != nullptr){
        Speed = Own->GetVelocity().Size();
 
        FVector InverseVector = UKismetMathLibrary::InverseTransformDirection(Own->GetTransform(),Own->GetVelocity());
        Angle = UKismetMathLibrary::MakeRotFromX(InverseVector).Yaw;
    }else
        UE_LOG(LogTemp,Warning,TEXT("MyAnimInstance class error, no Own Actor"));
}
