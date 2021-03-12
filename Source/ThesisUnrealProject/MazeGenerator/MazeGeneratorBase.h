// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include <vector>
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MazeGeneratorBase.generated.h"

UCLASS()
class THESISUNREALPROJECT_API AMazeGeneratorBase : public AActor{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMazeGeneratorBase();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "MazeGeneration")
	int length = 10;

	UPROPERTY(EditAnywhere, Category = "MazeGeneration")
	int heigth = 10;

	UPROPERTY(EditAnywhere, Category = "MazeGeneration")
	TSubclassOf<AActor> One_Wall;

	UPROPERTY(EditAnywhere, Category = "MazeGeneration")
	TSubclassOf<AActor> Two_Wall;
	
	UPROPERTY(EditAnywhere, Category = "MazeGeneration")
	TSubclassOf<AActor> Three_Wall;

	//std::vector<std::vector<ABo>> *Maze = nullptr;

	//Methods
	void printMaze();
	void createObstacle(int Obstacles);
	void createRoom();
};
