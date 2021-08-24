// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeGenerationCreation2.h"

#include "Containers/Array.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "MazeCell2.h"
#include "RoomMaze.h"
#include "../Elements/Maze/Maze.h"
#include "../Graph/Graph.h"

MazeGenerationCreation2::MazeGenerationCreation2(int Length, int Height, int MazeObstacle, int Maze2Room, TSubclassOf<AMazeCell2> CellClass,
        TArray<TArray<AMazeCell*>> *Maze, TArray<RoomMaze> *Rooms, Graph<AMazeCell2>* MazeGraph, UWorld* World,float Depth, AMaze* Maze2) {
            this->Length = Length;
            this->Height = Height;
            this->MazeObstacle = MazeObstacle;
            this->Maze2Room = Maze2Room;
            this->CellClass = CellClass;
            this->Maze = Maze;
            this->Rooms = Rooms;
            this->MazeGraph = MazeGraph;
            this->World = World;
            this->Depth = Depth;
            this->Maze2 = Maze2;
}

MazeGenerationCreation2::~MazeGenerationCreation2()
{
}

void MazeGenerationCreation2::StandardMazeCreation() {
    InitializeMaze();
    CreateMaze(MazeGraph->GetCurrentNode(),nullptr);
    PrintMaze();
    /*CreateObstacle(MazeObstacle);
    CreateRooms();
    CreateMaze();*/
}


//Used to draw the line for the visual graph
void MazeGenerationCreation2::PrintMaze() {
    TArray<AMazeCell2*> Nodes = MazeGraph->GetNodes();

    for (AMazeCell2* Cell : Nodes) {
		for(Side<AMazeCell2>* Edge: MazeGraph->GetSides(Cell)){
			DrawDebugLine(World,
			FVector(Edge->From->GetActorLocation().X, Edge->From->GetActorLocation().Y, Edge->From->GetActorLocation().Z + 1100), //700
			FVector(Edge->To->GetActorLocation().X,Edge->To->GetActorLocation().Y,Edge->To->GetActorLocation().Z + 1100),
			FColor(100, 0, 0),
			true,
			50.f,
			0,
			50.f);
		}
    }

    
    /*for (AMazeCell* Cell : Nodes) {
		UE_LOG(LogTemp,Warning,TEXT("%d %d: %i"), Cell->I,Cell->J,MazeGraph->GetSides(Cell).Num());
    }*/
}

//Create the different maze cells.
void MazeGenerationCreation2::InitializeMaze() {
    
    FTransform Transform;
    
    for (int i = 0; i < Height; i++) {
        TArray<AMazeCell*> Row;
        for (int j = 0; j < Length; j++) {
            
            FVector Origin(i * (-1100), j * 1100, Depth); //1100 --- 1.5
            FRotator Rotator;

            AMazeCell2* CellActor = World->SpawnActor<AMazeCell2>(CellClass,Origin,Rotator);
            CellActor->SetFolderPath(TEXT("MazePieces"));

            Transform.SetLocation(Origin);
            Maze2->CreateFloor(Transform);
            Maze2->CreateWalls(Transform);

            MazeGraph->AddNode(CellActor);

            if(i == 0 && j == 0)
                MazeGraph->SetCurrentNode(CellActor);

            TArray<AMazeCell2*> Cells = MazeGraph->GetNodes();

            //Add the sides to the maze

            if(j != 0 && j % Length != 0)
                MazeGraph->AddSide(CellActor,Cells[i*Height + j-1],0);

            if(i != 0 && i % Height != 0)
                MazeGraph->AddSide(CellActor,Cells[i*Height + j - Height],0);

        }
    }

    //This second loop is used just to geenerate the first vertical wall and the last horizontal one.
    for (int i = 0; i < Height; i++) {
            
            FVector Origin(+1100, i * 1100, Depth); //1100 --- 1.5
            Transform.SetLocation(Origin);
            Maze2->CreateVerticalWall(Transform);

            Origin = FVector(-1100 * i, +1100 * Length, Depth); //1100 --- 1.5
            Transform.SetLocation(Origin);
            Maze2->CreateHorizontalWall(Transform);

    }

}

//Generate the obstacle in the maze.
void MazeGenerationCreation2::CreateObstacle(int Obstacles) {
    std::vector<int> AlreadySelectedNumbers(0);
    int RowExtr, ColumnExtr;

    for (int i = 0; i < Obstacles; i++) {
        RowExtr = FMath::RandRange(0, Length - 1);
        ColumnExtr = FMath::RandRange(0, Height - 1);

        if (std::find(AlreadySelectedNumbers.begin(),
                      AlreadySelectedNumbers.end(),
                      (RowExtr + 1) * (ColumnExtr + 1)) ==
                AlreadySelectedNumbers.end() &&
            (*Maze)[RowExtr][ColumnExtr]->NumberRoom == -1) {
            // It doesn't work for Length != Heigth
            (*Maze)[RowExtr][ColumnExtr]->bIsObstacle = true;
            (*Maze)[RowExtr][ColumnExtr]->bIsVisited = true;
            (*Maze)[RowExtr][ColumnExtr]->HideObstacleWall();
            AlreadySelectedNumbers.push_back((RowExtr + 1) * (ColumnExtr + 1));
        } else
            i -= 1;
    }
}

void MazeGenerationCreation2::CreateRooms() {
    for (int i = 0; i < Maze2Room; i++) CreateRoomSize3();
    //CreateRoomSize2();
}

//Check for intersection and generate the room.
void MazeGenerationCreation2::CreateRoomSize2() {
    int RowExtr;
    int ColumnExtr;

    do {
        RowExtr = FMath::RandRange(0, Length - 2);
        ColumnExtr = FMath::RandRange(0, Height - 2);
    } while (CheckRoomIntersection(RowExtr, ColumnExtr,2) || (RowExtr == 0 && ColumnExtr == 0));

    TArray<AMazeCell*> Room;

    RoomWallHide(Room, RowExtr, ColumnExtr, Rooms->Num(),2);
    RoomMaze m(Room);
    Rooms->Add(m);
}

void MazeGenerationCreation2::CreateRoomSize3() {
    int RowExtr;
    int ColumnExtr;

    do {
        RowExtr = FMath::RandRange(1, Length - 4);
        ColumnExtr = FMath::RandRange(1, Height - 4);
    } while (CheckRoomIntersection(RowExtr, ColumnExtr,3) || (RowExtr == 0 && ColumnExtr == 0));

    TArray<AMazeCell*> Room;

    
    //RoomWallHide(Room, RowExtr, ColumnExtr, Rooms->Num());
    RoomWallHide(Room, RowExtr, ColumnExtr, Rooms->Num(),3);
    RoomMaze m(Room);
    Rooms->Add(m);
}

// Wrapper for recursion depth visit
void MazeGenerationCreation2::CreateMazeWrapper(int I, int J) {
    /*TArray<AMazeCell*> Neighbors;
    (*Maze)[I][J]->bIsVisited = true;
    //if I am not a room.
    if ((*Maze)[I][J]->NumberRoom == -1) {
        CheckForNeighbors(Neighbors, I, J);
        while (Neighbors.Num() != 0) {
            int NumExtr = FMath::RandRange(0, Neighbors.Num() - 1);
            MazeGraph->AddSide((*Maze)[I][J], Neighbors[NumExtr], 1);

            // Delete the wall from the 2 cells.
            if (I != Neighbors[NumExtr]->I)
                if (I > Neighbors[NumExtr]->I) {
                    (*Maze)[I][J]->HideWall(1);
                    (*Maze)[I - 1][J]->HideWall(3);
                } else {
                    (*Maze)[I][J]->HideWall(3);
                    (*Maze)[I + 1][J]->HideWall(1);
                }
            else {
                if (J > Neighbors[NumExtr]->J) {
                    (*Maze)[I][J]->HideWall(4);
                    (*Maze)[I][J - 1]->HideWall(2);
                } else {
                    (*Maze)[I][J]->HideWall(2);
                    (*Maze)[I][J + 1]->HideWall(4);
                }
            }

            CreateMazeWrapper(Neighbors[NumExtr]->I, Neighbors[NumExtr]->J);
            Neighbors.Empty();
            CheckForNeighbors(Neighbors, I, J);
        }
    } else{
        (*Rooms)[(*Maze)[I][J]->NumberRoom].bDoor = true;

    }*/
}

// Start the maze creation from (RowExtr, ColumnExtr)
void MazeGenerationCreation2::CreateMaze(AMazeCell2* Current,AMazeCell2* Previous) {

       if(!Current->bIsVisited){
        
        Current->bIsVisited = true;
        TArray<Side<AMazeCell2>*> Neighbors = MazeGraph->GetSides(Current);
        //CheckForNeighbors(Current, Neighbors);

        //NumberOfTimes the for loop will be execute
        int Cycles = Neighbors.Num();
        int Contator = 0;

        while(Contator < Cycles){
            
            int NumExtr = FMath::RandRange(0, Neighbors.Num() - 1);

            Side<AMazeCell2>* MazeCell = Neighbors[NumExtr];
            
            if(MazeCell->To->bIsVisited && MazeCell->To != Previous){
            
                MazeGraph->DeleteSide(Current,MazeCell->To);

            }else{
                Current->DestroyWall(MazeCell->To);
                CreateMaze(MazeCell->To,Current);
            }

            Neighbors.Remove(MazeCell);
            
            Contator++;

        }
    }


}

//check for intersection: first i check the 4 square that composed the room, then the nearby cells.
bool MazeGenerationCreation2::CheckRoomIntersection(int Row, int Column, int RoomSize) {

    //Check if the cells are already a room.
    /*for(int i = 0; i < RoomSize; i++){

        if((*Maze)[Row][Column]->NumberRoom != -1)
            return true;
    
    }*/

    return CheckNearbyRoom(Row, Column, 3);
}

//I push the neighbor if it hasn't been visited yet and, or it is not a room or if it is a room, it doesn't have a door.
void MazeGenerationCreation2::CheckForNeighbors(AMazeCell2* Current,TArray<AMazeCell2*>& Neighbors) {

    for(Side<AMazeCell2>* Cell : MazeGraph->GetSides(Current)){

        if(!Cell->To->bIsVisited)
            Neighbors.Add(Cell->To);

    }

}

bool MazeGenerationCreation2::CheckNearbyRoom(int Row, int Column, int RoomSize) {
    
    int StartRow = Row - 1;
    int StartColumn = Column - 1;

    for(int i = 0; i < RoomSize + 2; i++){

        for(int j = 0; j < RoomSize + 2; j++){
            
            if(StartRow + i >= 0 && StartRow + i < Length){

                if(StartColumn + j >= 0 && StartColumn + j < Length){

                    if((*Maze)[StartRow + i][StartColumn + j]->NumberRoom != -1)
                        return true;

                }

            }

        }

    }

    return false;

}

//Hide the wall that are useless in a room.
void MazeGenerationCreation2::RoomWallHide(TArray<AMazeCell*>& Room, int rowExtr, int columnExtr, int Pos, int WallsNumber) {

    for (int i = 0; i < WallsNumber; i++) {
        for (int j = 0; j < WallsNumber; j++) {
            
            (*Maze)[rowExtr + i][columnExtr + j]->NumberRoom = Pos;

            //If condition determine if I need to delete it (Can't delete the borders).
            if(j != 0)
                (*Maze)[rowExtr + i][columnExtr + j]->HideWall(4);
            
            if(i != 0)
                (*Maze)[rowExtr + i][columnExtr + j]->HideWall(1);
            
            if(j != (WallsNumber - 1))
                (*Maze)[rowExtr + i][columnExtr + j]->HideWall(2);
            
            if(i != (WallsNumber - 1))
                (*Maze)[rowExtr + i][columnExtr + j]->HideWall(3);

            //Delete the plane from the rooms8
            (*Maze)[rowExtr + i][columnExtr + j]->HideWall(0);
            
            Room.Add((*Maze)[rowExtr + i][columnExtr + j]);

        }
    }

}


