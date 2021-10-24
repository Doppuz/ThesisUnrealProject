// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "Graph/Graph.h"
#include "GameModeAbstract.h"
#include "CustomGameMode.generated.h"

class MazeGenerationCreation;
class MazeGenerationPopulate;
class AChestController;
class ACoinController;
class AGeneralElem;
class AdaptingExperienceManager;

UCLASS()
class THESISUNREALPROJECT_API ACustomGameMode : public AGameModeAbstract
{
	GENERATED_BODY()
	
public:
	
	ACustomGameMode();
    ~ACustomGameMode();

    float GetAchieverValue() const;
    float GetKillerValue() const;
    float GetExplorerValue() const;
    float GetSocializerValue() const;

    //NumberOfChest
    int NumberOfChest; 

    //NumberOfChest
    int NumberOfCoins; 

    
	virtual void StopGame(bool Enable);

 
protected:

    /** Called when the game starts. */
    virtual void BeginPlay() override;

//World percentage increment
    float MapIncrement;

};
