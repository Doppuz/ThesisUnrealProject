// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "../Graph/Graph.h"
#include "GameFramework/Actor.h"
#include "../Character/InterfaceMovableAI.h"
#include "MazeManager.generated.h"

class AMazeCell2;
class RoomMaze;
class MazeGenerationCreation2;
class AdaptingExperienceManager;
class AMazePopulate;
class AMaze;
class ADoor;
class AGeneralRoomWithDoor;
class ATrigger;
class AStair;
class AAIBull;
class AAIShooterPawn;
class APatrolAIPawn;
class AGeneralElem;
class ADoorKiller;
class ADoorRiddle;
class ADoorAchiever;
class ADoorExplorer;
class AShakingFallenPlatform;
class ACoinController;
class APortal;
class APuzzleButton;
class ARoomKiller;
class ASocializerMaze;
class APuzzleButtonPortal;
class APortalNight;
class APortalOpenDoor;
class ARoomAchiever;
class ADestructibleElements;
class AStatueInteractElem;
class AHeart;
class APawnInteractiveClass;
class ATrap;
class AGenericDestructibleElements;
class ATriggerSpawnAlly;

UCLASS()
class THESISUNREALPROJECT_API AMazeManager : public AActor{
	
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMazeManager();

	~AMazeManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

#pragma region MazeManager

//---------- Parameter for Maze generation ------------------

public:

	UPROPERTY(EditAnywhere, Category = "MazeGeneration")
	float Depth = 0;

	UPROPERTY(EditAnywhere, Category = "MazeGeneration")
	int Length = 10;

	UPROPERTY(EditAnywhere, Category = "MazeGeneration")
	int Height = 10;

	UPROPERTY(EditAnywhere, Category = "MazeGeneration")
	int MazeObstacle = 0;

	UPROPERTY(EditAnywhere, Category = "MazeGeneration")
	int MazeRooms = 4;
	
	UPROPERTY(EditAnywhere, Category = "MazeGeneration")
	bool PopulateMaze = true;

	UPROPERTY(EditAnywhere, Category = "MazeGeneration")
	TSubclassOf<AMazeCell2> CellClass;

	//Maze meshes actor.
	AMaze* MazeActor;

	//Graph of the maze
	Graph<AMazeCell2>* MazeGraph;

	TArray<TArray<AMazeCell2*>> MaxPaths;

protected:

	//Maze meshes actor
	UPROPERTY(EditAnywhere, Category = "MazeGeneration")
	TSubclassOf<AMaze> MazeActorClass;

	//Pointer to the AdaptingExperienceManager class
	AdaptingExperienceManager* Adapting;

	FVector PlayerPosition;

	//World percentage increment
    float MapIncrement;

#pragma endregion

#pragma region MazeCreation

public:
	
	void StandardMazeCreation();

	void PrintMaze(TArray<AMazeCell2*> Nodes,FColor Color);

	//Keep track of the center the rooms.
	TMap<int,FVector> RoomCenter;
	
	//Used to keep track of the rooms with a door.
	TArray<int> RoomWithDoor;

protected:

	//Methods
	void InitializeMaze();
	void CreateObstacle(int ObstaclesNumber);
	void CreateRooms(int);
	bool CheckRoomIntersection(TArray<AMazeCell2*>,int);
	void CreateMaze(AMazeCell2*,AMazeCell2*);

	//Distance between 2 cells.
	float Distance;

#pragma endregion

#pragma region Populate

public:

	//Class for trigger spawn
	UPROPERTY(EditAnywhere, Category = "Elements")
	TSubclassOf<ATrigger> TriggerClass;

	//Rooms
	UPROPERTY(EditAnywhere, Category = "Rooms")
	TSubclassOf<AGeneralRoomWithDoor> RumbleArenaClass;
	
	UPROPERTY(EditAnywhere, Category = "Rooms")
	TSubclassOf<AGeneralRoomWithDoor> EnemiesArenaClass;
	
	UPROPERTY(EditAnywhere, Category = "Rooms")
	TSubclassOf<AGeneralRoomWithDoor> MazeArenaClass;

	UPROPERTY(EditAnywhere, Category = "Rooms")
	TSubclassOf<AGeneralRoomWithDoor> RiddleArenaClass;

	//Contains the path that leads to the exit.
	TArray<AMazeCell2*> MaxPath;

	//Contains all the other paths that are not included in MaxPath.
	TArray<Graph<TArray<AMazeCell2*>>> OtherPaths;

	void Populate(TArray<AMazeCell2*>);

protected:

	UPROPERTY(EditAnywhere, Category = "Populate")
	TSubclassOf<ADoor> DoorClass;

	UPROPERTY(EditAnywhere, Category = "Populate")
	TSubclassOf<AGeneralElem> CrateClass;

	UPROPERTY(EditAnywhere, Category = "Enemies")
	TSubclassOf<AAIBull> BullEnemyClass;

	UPROPERTY(EditAnywhere, Category = "Enemies")
	TSubclassOf<AAIShooterPawn> ShooterEnemyClass;

	UPROPERTY(EditAnywhere, Category = "Enemies", meta=( MustImplement= "InterfaceMovableAI" ))
	TSubclassOf<APawn> PatrolEnemyClass;
	
	UPROPERTY(EditAnywhere, Category = "Enemies", meta=( MustImplement= "InterfaceMovableAI" ))
	TSubclassOf<APawn> PatrolEnemyCircularClass;

	UPROPERTY(EditAnywhere, Category = "Enemies", meta=( MustImplement= "InterfaceMovableAI" ))
	TSubclassOf<APawn> MoveAIClass;

	UPROPERTY(EditAnywhere, Category = "Enemies", meta=( MustImplement= "InterfaceMovableAI" ))
	TSubclassOf<APawn> MoveAIClass2;

	UPROPERTY(EditAnywhere, Category = "Elements")
	TSubclassOf<ADoorKiller> DoorKillerClass;
	
	UPROPERTY(EditAnywhere, Category = "Elements")
	TSubclassOf<ADoorRiddle> DoorRiddleClass;

	UPROPERTY(EditAnywhere, Category = "Elements")
	TSubclassOf<ADoorAchiever> DoorAchieverClass;
	
	UPROPERTY(EditAnywhere, Category = "Elements")
	TSubclassOf<ADoorExplorer> DoorExplorerClass;

	UPROPERTY(EditAnywhere, Category = "Elements")
	TSubclassOf<AShakingFallenPlatform> ShakingFallenPlatform;
	
	UPROPERTY(EditAnywhere, Category = "Elements")
	TSubclassOf<ACoinController> CoinClass;
	
	UPROPERTY(EditAnywhere, Category = "Elements")
	TSubclassOf<ACoinController> CoinHorizontalClass;

	UPROPERTY(EditAnywhere, Category = "Elements")
	TSubclassOf<APortal> PortalClass;

	UPROPERTY(EditAnywhere, Category = "Elements")
	TSubclassOf<APortalNight> PortalNightClass;

	UPROPERTY(EditAnywhere, Category = "Elements")
	TSubclassOf<APuzzleButton> PuzzleButtonClass;
	
	UPROPERTY(EditAnywhere, Category = "Elements")
	TSubclassOf<APuzzleButtonPortal> PuzzleButtonPortalClass;

	UPROPERTY(EditAnywhere, Category = "Elements")
	TSubclassOf<ARoomKiller> KillerRoomClass;

	UPROPERTY(EditAnywhere, Category = "Elements")
	TSubclassOf<ARoomAchiever> RoomAchieverClass;

	UPROPERTY(EditAnywhere, Category = "Elements")
	TSubclassOf<ASocializerMaze> SocializerMazeClass;
	
	UPROPERTY(EditAnywhere, Category = "Elements")
	TSubclassOf<ADestructibleElements> DestructibleShakeClass;
	
	UPROPERTY(EditAnywhere, Category = "Elements")
	TSubclassOf<AGenericDestructibleElements> DestrElem;
	
	UPROPERTY(EditAnywhere, Category = "Elements")
	TSubclassOf<AActor> MetalCrateClass;
	
	UPROPERTY(EditAnywhere, Category = "Elements")
	TSubclassOf<AStatueInteractElem> StatueClass;

	UPROPERTY(EditAnywhere, Category = "Elements")
	TSubclassOf<AHeart> HeartClass;

	UPROPERTY(EditAnywhere, Category = "Elements")
	TSubclassOf<APawnInteractiveClass> SpokenNpcClass;
	
	UPROPERTY(EditAnywhere, Category = "Elements")
	TSubclassOf<ATrap> TrapClass;
		
	UPROPERTY(EditAnywhere, Category = "Elements")
	TSubclassOf<ATriggerSpawnAlly> TriggerSpawnAllyClass;

	//Arena spawn positions.
	TArray<FVector> ArenaSpawnLocation;

	//At the beginning empty, They will contain all the speech and quetion taken from a file.
	TArray<TArray<FString>> Speech;
	TArray<TArray<FString>> Questions;
	//Used when the NPC is in the last cell of an other path.
	TArray<TArray<FString>> BlockedSpeech;

	//Memorize the questions and the speech already used.
	TArray<TArray<FString>> OldSpeech;
	TArray<TArray<FString>> OldQuestions;
	TArray<TArray<FString>> OldBlockedSpeech;

	void LoadFromFile(TArray<TArray<FString>>&, FString FileName);

	virtual void DepthVisit(AMazeCell2* Start);
	void DepthVisitWrapper(AMazeCell2* Current, float Cost, TArray<AMazeCell2*> CurrentVisitedCell,
		TArray<AMazeCell2*> & MazeCellList, Graph<AMazeCell2>* CurrentGraph);
	void SetDynamicVisitedToZero();
	void CreateOtherPaths(Graph<AMazeCell2>* OtherGraph, AMazeCell2* Current, AMazeCell2* Previous);

	void AddDoors(int);

	//Choose a room within a range to insert it in the level.
	void AddRoom(int, ADoor*, ADoor*, FVector, AMazeCell2*);

// --- Add enemies ---

	//Generate the enemies in the level
	void GenerateElements(TArray<AMazeCell2*> Path);

	//Add the enemy in the level
	void AddEnemy(int Index, AMazeCell2* Cell, TArray<AMazeCell2*> Path);

// --- Wrapper methods for adding enemy ---

	bool SetOffsetVector(AMazeCell2* AheadCell, AMazeCell2* BehindCell, FVector&, float Value);

	void LineTracing(FHitResult&,FVector, FVector);

	void GenerateDecorations(FVector, FVector, FVector,bool,TSubclassOf<AGeneralElem>);

	void GenerateSideActor(TSubclassOf<APawn> AIClass, int CellIndex, TArray<AMazeCell2*> Path);
	
	void GenerateSideElements(int CellIndex, int i, float HeightOffset, float SideOffset, float OffsetValue, bool, TSubclassOf<AGeneralElem>, TArray<AMazeCell2*> Path);

// --- Type Of Enemies ---

	void TypeOfMoveAlly(int CellIndex, int Index, TArray<AMazeCell2*> Path);
	
	void TypeOfPatrols(int CellIndex, int Index, TArray<AMazeCell2*> Path);

	void TypeOfEnemies(int Index, int CellIndex, TArray<AMazeCell2*> Path);

	void TypeOfCoinEnemies(int Index, int CellIndex, TArray<AMazeCell2*> Path);

// --- BlockedDoor Elements ---
	
	void GenerateDoors();

	void AddDoor(int Index, AMazeCell2* Cell);

	//Compare the position of the cells and return the right Rotation of the door.
	FRotator GetDoorRotation(AMazeCell2* AheadCell, AMazeCell2* BehindCell);

// --- Fallen Plat ---

	void AddFallenPlatforms(int Index, AMazeCell2* Cell, TArray<AMazeCell2*> Path);

	void CreatePlatforms(AMazeCell2* Cell, float Value);

// --- Portal Door ---
	void PortalType(int Index, AMazeCell2* Cell);

// --- OtherPaths ---

	void PopulateOtherPath();

	void SpawnExtraElem(int, AMazeCell2*,AMazeCell2*);

#pragma endregion

};
