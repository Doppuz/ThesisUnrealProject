// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MazeCellActor.generated.h"

UCLASS()
class THESISUNREALPROJECT_API AMazeCellActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMazeCellActor();
	void Init(UStaticMesh* mesh);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComponent;

	UStaticMesh* Mesh;

};
