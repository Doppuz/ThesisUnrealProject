// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GeneralElem.generated.h"

class ACoinController;

UCLASS()
class THESISUNREALPROJECT_API AGeneralElem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGeneralElem();
	
	bool ItHasCoin;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAcces = true), Category = "Destruction")
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAcces = true), Category = "Destruction")
	USceneComponent* SpawnCoinPosition;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAcces = true), Category = "DecorationElements")
	UStaticMeshComponent* MeshComponent1;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAcces = true), Category = "DecorationElements")
	UStaticMeshComponent* MeshComponent2;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAcces = true), Category = "DecorationElements")
	UStaticMeshComponent* MeshComponent3;
	
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAcces = true), Category = "DecorationElements")
	TArray<UStaticMesh*> Meshes;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAcces = true), Category = "Destruction")
	TSubclassOf<ACoinController> CoinClass;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAcces = true), Category = "DecorationElements")
	bool bNeedOtherElem;

};
