// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "PawnAllyNPC.generated.h"

class AGunController;
class ASquaredProjectile;

UCLASS()
class THESISUNREALPROJECT_API APawnAllyNPC : public APawn{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APawnAllyNPC();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = General)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = General)
	class UBoxComponent* Collider;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = General)
	UBoxComponent* TriggerDialog;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = General)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = General)
	USceneComponent* ProjectileSpawnPosition;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Movement)
	float JumpForce;

	//Projectile class
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Projectile)
	TSubclassOf<ASquaredProjectile> ProjectileClass;
	
	//Time between 2 projectile
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Projectile)
	float ProjectileTimeout;

	//Healt
	UPROPERTY(EditDefaultsOnly)
	float MaxHealth;

	UPROPERTY(VisibleAnywhere)
	float Health;
	
	void Jump();
	void SetJump();
	
	void Shoot();
	void SetShooting();

	//SpeakDialog 
	void Speak();
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Speak)
	TArray<FString> Speech;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = Speak)
	int SpeechContator;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	/** The widget class we will use as our dialog menu. */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
    TSubclassOf<UUserWidget> WidgetClass;

private:

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int otherBodyIndex, bool fromsweep, const FHitResult & Hit);
	
	UFUNCTION()
    void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	//Jump
	bool bAmIJump;
	FTimerHandle JumpTimer;

	//Shot
	bool bAmIShooting;
	FTimerHandle ShotTimer;
	
};
