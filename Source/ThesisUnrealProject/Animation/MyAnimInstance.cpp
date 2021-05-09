// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "../Character/CharacterController.h"

UMyAnimInstance::UMyAnimInstance() {
    Speed = 0.f;
}

void UMyAnimInstance::SetAttack() {
    //Attack = !Attack;
    //PlayAnimMontage(Montage,1, NAME_None);
}

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds) {
    
    Super::NativeUpdateAnimation(DeltaSeconds);
    AActor* Own = GetOwningActor();

    if(Own != nullptr){

        ACharacterController* CharController = Cast<ACharacterController>(Own); 

        Speed = Own->GetVelocity().Size();
 
        FVector InverseVector = UKismetMathLibrary::InverseTransformDirection(Own->GetTransform(),Own->GetVelocity());
        Angle = UKismetMathLibrary::MakeRotFromX(InverseVector).Yaw;

        APawn* Pawn = Cast<APawn>(Own);
        
        if(Pawn != nullptr){
	        AController* PawnController = Cast<AController>(Pawn->GetController());
	
            FVector Position;
            FRotator Rotation;

            if(PawnController != nullptr){
                PawnController->GetPlayerViewPoint(Position,Rotation);
                AngleArmRotation = FRotator(0,0,-Rotation.Pitch);

            }

            //Aim Rotation
            FRotator ControlRotator = Pawn->GetControlRotation();
            FRotator ActorRotator = Pawn->GetActorRotation();
            PitchAngle = UKismetMathLibrary::NormalizedDeltaRotator(ControlRotator,ActorRotator).Pitch;

            if(CharController != nullptr){
                IsRestPose = CharController->GetRestPose();
                //Acceleration
                if(CharController->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0){
                    IsAcceleration = true;
                    UE_LOG(LogTemp,Warning,TEXT("%f"),CharController->GetCharacterMovement()->GetCurrentAcceleration().Size() );
                }else{
                    IsAcceleration = false;
                }
                
            }

        }
        
    }else
        UE_LOG(LogTemp,Warning,TEXT("MyAnimInstance class error, no Own Actor"));
}
