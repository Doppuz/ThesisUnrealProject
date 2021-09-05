// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MazeCell2.generated.h"

UCLASS()
class THESISUNREALPROJECT_API AMazeCell2 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMazeCell2();

	bool bIsVisited;
	
	bool bIsRoom;

	int RoomNumber;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	void DestroyWall(AMazeCell2*);
	void DestroyFloor();

	// == Operator overloading
	FORCEINLINE bool operator == (const AMazeCell2 &Other){
		
		return GetName() == Other.GetName();

	}

protected:

	void LineTracing(FVector);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};
