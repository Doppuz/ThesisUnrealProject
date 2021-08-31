// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneralUndergroundRoom.h"
#include "../../../GameManager/MazeManager.h"
#include "../../../GameManager/MazeCell2.h"
#include "../../Maze/Maze.h"
#include "../../../Elements/GeneralElements/Door.h"
#include "../../../Elements/Stairs/Stair.h"


void AGeneralUndergroundRoom::BeginPlay() {
    
    Super::BeginPlay();

    FTransform SpawnLocAndRotation;
    MazeManager = GetWorld()->SpawnActorDeferred<AMazeManager>(MazeManagerClass, SpawnLocAndRotation);
    MazeManager->Depth = -750.f;
    MazeManager->Length = 5;
    MazeManager->Height = 5;
    MazeManager->MazeRooms = 0;
    MazeManager->PopulateMaze = false;
    MazeManager->FinishSpawning(SpawnLocAndRotation);

    MazeManager->MazeActor->WallInstances->RemoveInstance(0);

}

void AGeneralUndergroundRoom::PositionateRoom(AMazeCell2* RoomCell) {
    
    FVector Location;
    AStair* Stair;
    FVector MazeLocation;
    FVector DoorPos;

    FVector StairsLocation = RoomDoor->GetActorLocation();
    StairsLocation.Z = -100.f;

    //If condition to rotate the stair and the room according to the door.
    if(RoomDoor->GetActorLocation().X == RoomCell->GetActorLocation().X){
            
        //Check if the everything haa to be positionate on the right or left side.
        if(RoomCell->GetActorLocation().Y > RoomDoor->GetActorLocation().Y){
                    
            Stair = GetWorld()->SpawnActor<AStair>(StairClass, StairsLocation,RoomDoor->GetActorRotation() + FRotator(0.f,90.f,0.f)); 
            MazeLocation = FVector(RoomDoor->GetActorLocation().X,RoomDoor->GetActorLocation().Y + Stair->StepsDistance * Stair->StepsNumber + Stair->InitialOffset,
                Stair->StepsHeightDistance * (Stair->StepsNumber - 1));
            MazeManager->MazeActor->SetActorLocation(MazeLocation);
            //Here SetMazeRotation is useless because it would be Fotator(0.f,0.f,0.f).
            DoorPos = MazeLocation - FVector(0.f,Stair->InitialOffset,0.f);

        }else{
                    
            Stair = GetWorld()->SpawnActor<AStair>(StairClass, StairsLocation,RoomDoor->GetActorRotation() - FRotator(0.f,90.f,0.f));  
            MazeLocation = FVector(RoomDoor->GetActorLocation().X,RoomDoor->GetActorLocation().Y - Stair->StepsDistance * Stair->StepsNumber - Stair->InitialOffset,
                Stair->StepsHeightDistance * (Stair->StepsNumber - 1));
            MazeManager->MazeActor->SetActorLocation(MazeLocation);
            MazeManager->MazeActor->SetActorRotation(FRotator(0.f,180.f,0.f));
            //Change the position of the room door accroding to the new room.
            DoorPos = MazeLocation + FVector(0.f,Stair->InitialOffset,0.f);

        }
                    
    }else{


        if(RoomCell->GetActorLocation().X > RoomDoor->GetActorLocation().X){
                                    
            Stair = GetWorld()->SpawnActor<AStair>(StairClass, StairsLocation,RoomDoor->GetActorRotation() - FRotator(0.f,90.f,0.f));  
            MazeLocation = FVector(RoomDoor->GetActorLocation().X + Stair->StepsDistance * Stair->StepsNumber + Stair->InitialOffset,RoomDoor->GetActorLocation().Y,
                Stair->StepsHeightDistance * (Stair->StepsNumber - 1));
            MazeManager->MazeActor->SetActorLocation(MazeLocation);
            MazeManager->MazeActor->SetActorRotation(FRotator(0.f,-90.f,0.f));
                    
            DoorPos = MazeLocation - FVector(Stair->InitialOffset,0.f,0.f);;
              
        }else{

            Stair = GetWorld()->SpawnActor<AStair>(StairClass, StairsLocation,RoomDoor->GetActorRotation() + FRotator(0.f,90.f,0.f)); 
            MazeLocation = FVector(RoomDoor->GetActorLocation().X - Stair->StepsDistance * Stair->StepsNumber - Stair->InitialOffset,RoomDoor->GetActorLocation().Y,
                Stair->StepsHeightDistance * (Stair->StepsNumber - 1));
            MazeManager->MazeActor->SetActorLocation(MazeLocation);
            MazeManager->MazeActor->SetActorRotation(FRotator(0.f,90.f,0.f)); 
            DoorPos = MazeLocation + FVector(Stair->InitialOffset,0.f,0.f);;

        }
    }

    //Change the position of the door of the underground maze.
    DoorPos.Z += 400.f;
    RoomDoor->SetActorLocation(DoorPos);
    RoomDoor->SetDoorDirection(true);
    RoomDoor->Speed = 3.0f;
    RoomDoor->SetActorScale3D(FVector(1.7f,3.f,0.75f));

}
