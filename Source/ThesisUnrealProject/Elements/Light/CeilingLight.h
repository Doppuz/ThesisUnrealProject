// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/PointLightComponent.h"
#include "CeilingLight.generated.h"

UCLASS()
class THESISUNREALPROJECT_API ACeilingLight : public AActor{

	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACeilingLight();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
	UPointLightComponent* Light;

};
