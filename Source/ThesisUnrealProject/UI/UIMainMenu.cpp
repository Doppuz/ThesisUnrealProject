// Fill out your copyright notice in the Description page of Project Settings.


#include "UIMainMenu.h"
#include "Components/TextBlock.h"
#include "UIButton.h"
#include "UIAnswer.h"
#include "UIBox.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Border.h"
#include "Components/SizeBox.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../GameInstance/BartleManagerGameInstance.h"
#include "../CheckPoints/SaveGameData.h"
#include "GameFramework/PlayerStart.h"
#include "../GameModeTutorial.h"

void UUIMainMenu::NativeConstruct() {
    
    Super::NativeConstruct();

    ButtonPlay->Text->SetText(FText::FromString("Play"));
    ButtonPlay->ButtonPlay->OnClicked.AddDynamic(this,&UUIMainMenu::OnButtonPlayClicked);

    ButtonQuit->Text->SetText(FText::FromString("Quit"));
    ButtonQuit->ButtonPlay->OnClicked.AddDynamic(this,&UUIMainMenu::OnButtonQuitClicked);

    Switcher->SetActiveWidgetIndex(0);
    
    Answer1->Answer->SetText(FText::FromString("Start"));
    Answer2->Answer->SetText(FText::FromString("Start"));
    
    Answer1->AnswerButton->OnClicked.AddDynamic(this,&UUIMainMenu::Answer1Clicked);
    
    Answer2->AnswerButton->OnClicked.AddDynamic(this,&UUIMainMenu::Answer2Clicked);

    DialogTextContator = -1;

    TextBox->SetNPCName("");
    TextBox->BorderBox->SetBrushColor(FLinearColor(0.072917f,0.072917f,0.072917f,0.8f));
    TextBox->SetDialogText("HI! Before Playing the game, I ask you to answer the question. Don't exit before finishing it.");

    MapDialogText.Add(0 , {"Which is more enjoyable to you?","Killing a big monster","Bragging about it to your friends"});
    AnswerChoice.Add(0,{Type::Achiever,Type::Socializer});

    MapDialogText.Add(1 , {"Which do you enjoy more in quests?","Getting involved in the storyline","Getting the rewards at the end"});
    AnswerChoice.Add(1,{Type::Socializer,Type::Achiever});
    
    MapDialogText.Add(2 , {"Which would you rather be noticed for in an online game?"," Your equipment","Your personality"});
    AnswerChoice.Add(2,{Type::Achiever,Type::Socializer});

    MapDialogText.Add(3 , {"Which do you enjoy more in an online game?","Getting the latest gossip", "Getting a new item"});
    AnswerChoice.Add(3,{Type::Socializer,Type::Achiever});

    MapDialogText.Add(4 , {"Which would you rather have, as a player in an online game?","A private channel over which you and your friends can communicate","Your own house, worth millions of gold coins"});
    AnswerChoice.Add(4,{Type::Socializer,Type::Achiever});

    MapDialogText.Add(5 , {"Which would you enjoy more as an online game player?","Running your own tavern?" ,"Making your own maps of the world, then selling them"});
    AnswerChoice.Add(5,{Type::Socializer,Type::Explorer});

    MapDialogText.Add(6 , {"What's more important in an online game to you?","The number of people", "The number of areas to explore"});
    AnswerChoice.Add(6,{Type::Socializer,Type::Explorer});

    MapDialogText.Add(7 , {"What's more important to you?", "The quality of roleplaying in an online game","The uniqueness of the features, and game mechanic"});
    AnswerChoice.Add(7,{Type::Socializer,Type::Explorer});

    MapDialogText.Add(8 , {"You are being chased by a monster in an online game. Do you:","Ask a friend for help in killing it", "Hide somewhere you know the monster won't follow?"});
    AnswerChoice.Add(8,{Type::Socializer,Type::Explorer});

    MapDialogText.Add(9 , {"You're a player in an online game, and about to go into an unknown dungeon. You have your choice of one more person for your party. Do you bring:",
        "A bard, who's a good friend of yours and who's great for entertaining you and your friends","  A wizard, to identify the items that you find there?"});
    AnswerChoice.Add(9,{Type::Socializer,Type::Explorer});

    MapDialogText.Add(10 , {"Someone has PK'ed you (killed you in player vs. player combat). Do you want to:","Find out why, and try to convince them not to do it again ", "Plot your revenge?"});
    AnswerChoice.Add(10,{Type::Socializer,Type::Killer});

    MapDialogText.Add(11 , {"Which is more exciting?", "A well-roleplayed scenario", "A deadly battle"});
    AnswerChoice.Add(11,{Type::Socializer,Type::Killer});

    MapDialogText.Add(12 , {"Which would you enjoy more?","Winning a duel with another player","Getting accepted by a clan (a group of other players)"});
    AnswerChoice.Add(12,{Type::Killer,Type::Socializer});

    MapDialogText.Add(13 , {"Is it better to be: ","Feared", "Loved"});
    AnswerChoice.Add(13,{Type::Killer,Type::Socializer});
    
    MapDialogText.Add(14 , {"Would you rather:","Hear what someone has to say","Show them the sharp blade of your axe?"});
    AnswerChoice.Add(14,{Type::Socializer,Type::Killer});

    MapDialogText.Add(15 , {"In an online game, a new area opens up. Which do you look forward to more?",
        "Exploring the new area, and finding out its history","Being the first to get the new equipment from the area"});
    AnswerChoice.Add(15,{Type::Explorer,Type::Achiever});

    MapDialogText.Add(16 , {"In an online game, would you rather be known as:","Someone who can run from any two points in the world, and really knows their way around","The person with the best, most unique equipment in the game?"});
    AnswerChoice.Add(16,{Type::Explorer,Type::Achiever});

    MapDialogText.Add(17 , {"Would you rather:","Become a hero faster than your friends","Know more secrets than your friends?"});
    AnswerChoice.Add(17,{Type::Achiever,Type::Explorer});

    MapDialogText.Add(18 , {"Do you tend to:","Know things no one else does","Have items no one else does?"});
    AnswerChoice.Add(18,{Type::Explorer,Type::Achiever});

    MapDialogText.Add(19 , {"Which would you rather do:","Solve a riddle no one else has solved","Getting to a certain experience level faster than anyone else?"});
    AnswerChoice.Add(19,{Type::Explorer,Type::Achiever});

    MapDialogText.Add(20 , {"In an online game, would rather join a clan of:","Scholars","Assassins?"});
    AnswerChoice.Add(20,{Type::Explorer,Type::Killer});

    MapDialogText.Add(21 , {"Would you rather win:","A trivia contest","An arena battle?"});
    AnswerChoice.Add(21,{Type::Explorer,Type::Killer});
    
    MapDialogText.Add(22 , {"If you're alone in an area, do you think:","It's safe to explore","You'll have to look elsewhere for prey?"});
    AnswerChoice.Add(22,{Type::Explorer,Type::Killer});

    MapDialogText.Add(23 , {"You learn that another player is planning your demise. Do you:",
        "Go to an area your opponent is unfamiliar with and prepare there","Attack them before he attacks you?"});
    AnswerChoice.Add(23,{Type::Explorer,Type::Killer});

    MapDialogText.Add(24 , {"You meet a new player. Do you think of them as:",
        "Someone who can appreciate your knowledge of the game","As potential prey?"});
    AnswerChoice.Add(24,{Type::Explorer,Type::Killer});

    MapDialogText.Add(25 , {"In an online game, would you rather:","Have a sword twice as powerful as any other in the game","Be the most feared person in the game?"});
    AnswerChoice.Add(25,{Type::Achiever,Type::Killer});

    MapDialogText.Add(26 , {"In an online game, would you be more prone to brag about:","How many other players you've killed","Your equipment?"});
    AnswerChoice.Add(26,{Type::Killer,Type::Achiever});

    MapDialogText.Add(27 , {"Would you rather have:","A spell to damage other players","A spell that increases the rate at which you gain experience points?"});
    AnswerChoice.Add(27,{Type::Killer,Type::Achiever});

    MapDialogText.Add(28 , {"Would you rather receive as a quest reward:","Experience points","A wand with 3 charges of a spell that lets you control other players, against their will?"});
    AnswerChoice.Add(28,{Type::Achiever,Type::Killer});

    MapDialogText.Add(29 , {"When playing a video game, is it more fun to:","Have the highest score on the list","Beat your best friend one-on-one?"});
    AnswerChoice.Add(29,{Type::Achiever,Type::Killer});
    
}

void UUIMainMenu::OnButtonPlayClicked() {
    
    //UGameplayStatics::OpenLevel(GetWorld(), "Tutorial");
    Switcher->SetActiveWidgetIndex(1);

}

void UUIMainMenu::OnButtonQuitClicked() {

    UGameplayStatics::GetPlayerController(GetWorld(),0)->ConsoleCommand("quit");
    
}

void UUIMainMenu::Answer1Clicked() {
    
    DialogInteraction(0,1);
    
}

void UUIMainMenu::Answer2Clicked() {
    
    DialogInteraction(1,0);

}

//Parameter used for choosing which bartle value increase.
void UUIMainMenu::DialogInteraction(int Increase, int Decrease) {

    //Bartle Update
    if(DialogTextContator >= 0 && DialogTextContator < MapDialogText.Num()){
            UBartleManagerGameInstance* Bartle = Cast<UBartleManagerGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
            Bartle->EquallyDistributedUpdate(AnswerChoice[DialogTextContator][Increase],50.f/15.f,AnswerChoice[DialogTextContator][Decrease],50.f/15.f);        
    }

    DialogTextContator += 1;

    //Shows all the questions. After shows an end message and then Start the game.
    if(DialogTextContator < MapDialogText.Num()){

        //Set the dialog box with the first value of the TMap
        TextBox->SetNPCName("Question "+FString::FromInt(DialogTextContator + 1));
        TextBox->SetDialogText(MapDialogText[DialogTextContator][0]);
        Answer1->Answer->SetText(FText::FromString(MapDialogText[DialogTextContator][1]));
        Answer2->Answer->SetText(FText::FromString(MapDialogText[DialogTextContator][2]));

    }else if (DialogTextContator == MapDialogText.Num()){
        TextBox->SetDialogText("Thank you to answering all the questions! It's now time to start the test!");
        Answer1->Answer->SetText(FText::FromString("Continue"));
        Answer2->Answer->SetText(FText::FromString("Continue"));
        DialogTextContator += 1;
    }else{
        //Save the initial initial information for the game and store the value of the questionary
        UBartleManagerGameInstance* Bartle = Cast<UBartleManagerGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
        Bartle->TypesQuestionary = Bartle->Types;
        Bartle->ResetValue();

        if (USaveGameData* SaveGameInstance = Cast<USaveGameData>(UGameplayStatics::CreateSaveGameObject(USaveGameData::StaticClass()))){

			// Set data on the savegame object.
			SaveGameInstance->PlayerLocation = FVector(0.f,0.f,900000.22f);

			SaveGameInstance->AchieverQ = Bartle->TypesQuestionary[Achiever];
			SaveGameInstance->KillerQ = Bartle->TypesQuestionary[Killer];
			SaveGameInstance->ExplorerQ = Bartle->TypesQuestionary[Explorer];
			SaveGameInstance->SocializerQ = Bartle->TypesQuestionary[Socializer];

            SaveGameInstance->Achiever = 50.f;
			SaveGameInstance->Killer = 50.f;
			SaveGameInstance->Explorer = 50.f;
			SaveGameInstance->Socializer = 50.f;

            TArray<FName> Level = {"FirstPuzzle"};

			SaveGameInstance->Levels = Level;

			// Start async save process.
			UGameplayStatics::AsyncSaveGameToSlot(SaveGameInstance, "Checkpoint", 0);

        }

        //AGameModeTutorial* GameMode = Cast<AGameModeTutorial>(GetWorld()->GetAuthGameMode());
		//GameMode->ChangeMenuWidget(UIExplanation);

        
        UGameplayStatics::GetPlayerController(GetWorld(),0)->SetInputMode(FInputModeGameOnly());
        UGameplayStatics::OpenLevel(GetWorld(),"Tutorial");

    }

}