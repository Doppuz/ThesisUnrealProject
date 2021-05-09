#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "CharacterControllerFighter.generated.h"

class AGunController;

UCLASS()
class THESISUNREALPROJECT_API ACharacterControllerFighter : public ACharacter{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterControllerFighter();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = Camera)
	USpringArmComponent* CameraArmComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = Camera)
	UCameraComponent* CameraComponent;

	void MoveForward(float Axis);
	void MoveRight(float Axis); 
	void Shoot();

	bool AttackPose;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit);
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	
	void ChangeAttack();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGunController> GunClass;

	UPROPERTY()
	AGunController* Gun;
	
	class UMyAnimInstance* Anim;

	FTimerHandle AttackTimer;

	//Animation

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Generic", meta =(AllowPrivateAccess = "true"))
	UAnimMontage* Montage;

};
