// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "../Character/AllyAI/PawnInteractiveClass.h"
#include "SaveGameLevel1.generated.h"

class AMaze;
class AGenericDestructibleElements;

//To create an array of array of strings.
USTRUCT() struct FSpeech{

    GENERATED_BODY()

	UPROPERTY()
	TArray<FString> String;

};

//Include all the information about speech and question
USTRUCT() struct FSpeakActor{

    GENERATED_BODY()

	UPROPERTY()
	TArray<FString> Speech;

	UPROPERTY()
	FQuestion Questions;
	
	UPROPERTY()
	int QuestionAt;

	UPROPERTY()
	int RightAnswerPos;

	UPROPERTY()
	bool bAlreadySpoken;
};


//Value to be saved to restore the maze actor.
USTRUCT() struct FMazeValue{

    GENERATED_BODY()

	UPROPERTY()
	FVector Position;
	
	UPROPERTY()
	TArray<FTransform> TransformsFloor;

	UPROPERTY()
	TArray<FTransform> TransformsWall;
	
	UPROPERTY()
	TArray<FTransform> TransformsObstacle;
	
	UPROPERTY()
	TArray<FTransform> TransformsMetalCrate;

};

USTRUCT() struct FGeneralActor : public FSpeakActor{

    GENERATED_BODY()

	UPROPERTY()
	FTransform Transform;
	
	UPROPERTY()
	TSubclassOf<AActor> ActorClass;

	UPROPERTY()
	int ID;

};

USTRUCT() struct FDoorActor : public FGeneralActor{

    GENERATED_BODY()

	UPROPERTY()
	bool bOpenDoor;

	UPROPERTY()
	FVector FinalPosition;

};

USTRUCT() struct FMoveActor : public FSpeakActor{

    GENERATED_BODY()

	UPROPERTY()
	FTransform Transform;
	
	UPROPERTY()
	TSubclassOf<AActor> ActorClass;
	
	UPROPERTY()
	TArray<FVector> Positions;

	UPROPERTY()
	int StartIndex;

	UPROPERTY()
	bool StartDirection;

};

// Destructible actor structure

USTRUCT() struct FDestrActor : public FGeneralActor {
	
	GENERATED_BODY()

	UPROPERTY()
	TSubclassOf<AActor> SpawnActor;

};

// Door Achiever

USTRUCT() struct FDoorAchieverStruct : public FDoorActor{

    GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	int IDKey;

	UPROPERTY(VisibleAnywhere)
	TArray<int> IDs;

};

// Door Killer

USTRUCT() struct FDoorKillerStruct : public FDoorActor{

    GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	TArray<int> IDs;

};

USTRUCT() struct FNightPortal{

    GENERATED_BODY()

	UPROPERTY()
	FTransform Transform;
	
	UPROPERTY()
	TSubclassOf<AActor> ActorClass;

	UPROPERTY()
	FVector NewPosition;

};

USTRUCT() struct FPuzzlePortalStruct{

    GENERATED_BODY()

	UPROPERTY()
	FTransform Transform;
	
	UPROPERTY()
	TSubclassOf<AActor> ActorClass;

	UPROPERTY()
	FVector EndSpawnPosition;
	
	UPROPERTY()
	int DoorID;

};

USTRUCT() struct FRoomKillerStruct{

    GENERATED_BODY()

	UPROPERTY()
	FTransform Transform;
	
	UPROPERTY()
	TSubclassOf<AActor> ActorClass;

	UPROPERTY()
	FVector StartPortalPos;
	
	UPROPERTY()
	int DoorID;

	UPROPERTY()
	int NPCID;

};

USTRUCT() struct FRoomAchieverStruct{

    GENERATED_BODY()

	UPROPERTY()
	FTransform Transform;
	
	UPROPERTY()
	TSubclassOf<AActor> ActorClass;

	UPROPERTY()
	FVector EndPos;
	
	UPROPERTY()
	int DoorID;

	UPROPERTY()
	TArray<int> EnemiesID;

};


UCLASS()
class THESISUNREALPROJECT_API USaveGameLevel1 : public USaveGame{

	GENERATED_BODY()

public:
	
	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	TMap<int, FMazeValue> MazeTransformMap;
	
	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	TArray<FDestrActor> DestructibleElem;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	TArray<FGeneralActor> CoinElem;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	TArray<FGeneralActor> TrapElem;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	TArray<FGeneralActor> HatElem;
	
	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	TArray<FGeneralActor> HeartElem;
	
	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	TArray<FGeneralActor> FallenPlatformElem;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	TArray<FDoorActor> Doors;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	TArray<FDoorActor> DoorsRiddle;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	TArray<FDoorAchieverStruct> DoorsAchiever;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	TArray<FDoorKillerStruct> DoorsKiller;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	TArray<FDoorActor> DoorsExplorer;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	TArray<FGeneralActor> Enemies;
	
	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	TArray<FGeneralActor> Allies;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	TArray<FMoveActor> Patrols;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	TArray<FMoveActor> MoveAllies;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	TArray<FGeneralActor> Checkpoints;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	TArray<FMoveActor> Storms;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	TArray<FNightPortal> NightPortals;
	
	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	TArray<FPuzzlePortalStruct> PuzzlePortals;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	FRoomKillerStruct RoomKillerStruct;
	
	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	FRoomAchieverStruct RoomAchieverStruct;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	FGeneralActor LastActor;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	TArray<FSpeech> Speech;
	
	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	TArray<FSpeech> Questions;
	
	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	TArray<FSpeech> BlockedSpeech;
	
	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	TArray<FSpeech> OldSpeech;
	
	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	TArray<FSpeech> OldQuestions;
	
	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	TArray<FSpeech> OldBlockedSpeech;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	int DestrID;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	int EnemyID;
	
	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	int AllyID;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	FVector PlayerPos;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	FRotator PlayerRot;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	int Coins;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	int EnemiesDefeated;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	int SpokenAllies;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	int Statues;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	int TotalCoins;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	int TotalEnemiesDefeated;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	int TotalSpokenAllies;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	int TotalStatues;


};
