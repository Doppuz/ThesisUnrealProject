// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeGenerationCreation.h"

#include "../Graph/Graph.h"
#include "Containers/Array.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "MazeCell.h"
#include "RoomMaze.h"
#include "../Character/CustomPlayerStart.h"

MazeGenerationCreation::MazeGenerationCreation(int Length, int Height, int MazeObstacle, int Maze2Room, TSubclassOf<AMazeCell> CellClass,
        TArray<TArray<AMazeCell*>> *Maze, TArray<RoomMaze> *Rooms, Graph* MazeGraph, UWorld* World) {
            this->Length = Length;
            this->Height = Height;
            this->MazeObstacle = MazeObstacle;
            this->Maze2Room = Maze2Room;
            this->CellClass = CellClass;
            this->Maze = Maze;
            this->Rooms = Rooms;
            this->MazeGraph = MazeGraph;
            this->World = World;
}

MazeGenerationCreation::~MazeGenerationCreation()
{
}

void MazeGenerationCreation::StandardMazeCreation() {
    InitializeMaze();
    
    CreateObstacle(MazeObstacle);
    CreateRooms();
    CreateMaze();
}


//Used to draw the line for the visual graph
void MazeGenerationCreation::PrintMaze() {
    TArray<AMazeCell*> Nodes = MazeGraph->GetNodes();

    for (AMazeCell* Cell : Nodes) {
		for(Side* Edge: MazeGraph->GetSides(Cell)){
			DrawDebugLine(World,
			FVector(Edge->From->GetActorLocation().X, Edge->From->GetActorLocation().Y, Edge->From->GetActorLocation().Z + 700), //700
			FVector(Edge->To->GetActorLocation().X,Edge->To->GetActorLocation().Y,Edge->To->GetActorLocation().Z + 700),
			FColor(20, 50, 90),
			true,
			50.f,
			0,
			50.f);
		}
    }

    
    for (AMazeCell* Cell : Nodes) {
		UE_LOG(LogTemp,Warning,TEXT("%d %d: %i"), Cell->I,Cell->J,MazeGraph->GetSides(Cell).Num());
    }
}

//Create the different maze cells.
void MazeGenerationCreation::InitializeMaze() {
    for (int i = 0; i < Height; i++) {
        TArray<AMazeCell*> Row;
        for (int j = 0; j < Length; j++) {
            FVector Origin(i * (-1100) * 1.5, j * 1100 * 1.5, 0); //1100
            FRotator Rotation(0, 0, 0);
            AMazeCell* CellActor =
                World->SpawnActor<AMazeCell>(CellClass, Origin, Rotation);
            CellActor->I = i;
            CellActor->J = j;
            CellActor->SetFolderPath(TEXT("MazePieces"));
            MazeGraph->AddNode(CellActor);
            Row.Add(CellActor);
        }
        Maze->Add(Row);
    }
}

//Generate the obstacle in the maze.
void MazeGenerationCreation::CreateObstacle(int Obstacles) {
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
            // It doesn't worll for Legth != Heigth
            (*Maze)[RowExtr][ColumnExtr]->bIsObstacle = true;
            (*Maze)[RowExtr][ColumnExtr]->bIsVisited = true;
            (*Maze)[RowExtr][ColumnExtr]->HideObstacleWall();
            AlreadySelectedNumbers.push_back((RowExtr + 1) * (ColumnExtr + 1));
        } else
            i -= 1;
    }
}

void MazeGenerationCreation::CreateRooms() {
    for (int i = 0; i < Maze2Room; i++) CreateRoomSize2();
}

//Check for intersection and generate the room.
void MazeGenerationCreation::CreateRoomSize2() {
    int RowExtr;
    int ColumnExtr;

    do {
        RowExtr = FMath::RandRange(0, Length - 2);
        ColumnExtr = FMath::RandRange(0, Height - 2);
    } while (CheckRoomIntersection(RowExtr, ColumnExtr) || (RowExtr == 0 && ColumnExtr == 0));

    TArray<AMazeCell*> Room;

    RoomWallHide(Room, RowExtr, ColumnExtr, Rooms->Num());
    RoomMaze m(Room);
    Rooms->Add(m);
}

// Wrapper for recursion depth visit
void MazeGenerationCreation::CreateMazeWrapper(int I, int J) {
    TArray<AMazeCell*> Neighbors;
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

    //I was developping the 
        /*if(J+2 < 10){
         
            (*Maze)[I][J + 1]->HideWall(2);
            (*Maze)[I][J + 2]->HideWall(4);

            CreateMazeWrapper(I, J + 2); 

        }else if (I+2 < 10){
            
            (*Maze)[I + 1][J]->HideWall(3);
            (*Maze)[I + 2][J]->HideWall(1);

            CreateMazeWrapper(I + 2, J);
        }*/
    }
}

// Start the maze creation from (RowExtr, ColumnExtr)
void MazeGenerationCreation::CreateMaze() {
    int CellProcessed = 0;
    int RowExtr;
    int ColumnExtr;
    do {
        RowExtr = FMath::RandRange(0, Length - 1);
        ColumnExtr = FMath::RandRange(0, Height - 1);
    } while ((*Maze)[RowExtr][ColumnExtr]->NumberRoom != -1 ||
             (*Maze)[RowExtr][ColumnExtr]->bIsObstacle);
    
    //Change Player start pos, but useless.
    /*TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(World, ACustomPlayerStart::StaticClass(), FoundActors);
    FVector CellLocation = (*Maze)[RowExtr][ColumnExtr]->GetActorLocation();
    FoundActors[0]->SetActorLocation(FVector(CellLocation.X,CellLocation.Y,1000));*/

    CreateMazeWrapper(RowExtr, ColumnExtr);
}

//check for intersection: first i check the 4 square that composed the room, then the nearby cells.
bool MazeGenerationCreation::CheckRoomIntersection(int Row, int Column) {
    bool RoomInters = (*Maze)[Row][Column]->NumberRoom != -1 ||
                      (*Maze)[Row][Column + 1]->NumberRoom != -1 ||
                      (*Maze)[Row + 1][Column]->NumberRoom != -1 ||
                      (*Maze)[Row + 1][Column + 1]->NumberRoom != -1 ||
                      (*Maze)[Row][Column]->bIsObstacle ||
                      (*Maze)[Row][Column + 1]->bIsObstacle ||
                      (*Maze)[Row + 1][Column]->bIsObstacle ||
                      (*Maze)[Row + 1][Column + 1]->bIsObstacle;

    if (RoomInters) return true;

    return CheckNearbyRoom(Row, Column, 2);
}

//I push the neighbor if it hasn't been visited yet and, or it is not a room or if it is a room, it doesn't have a door.
void MazeGenerationCreation::CheckForNeighbors(TArray<AMazeCell*>& Neighbors, int i,
                                           int j) {
    if (i != 0 && !(*Maze)[i - 1][j]->bIsVisited &&
        ((*Maze)[i - 1][j]->NumberRoom == -1 ||
         !(*Rooms)[(*Maze)[i - 1][j]->NumberRoom].bDoor))
        Neighbors.Push((*Maze)[i - 1][j]);

    if (i != (Length - 1) && !(*Maze)[i + 1][j]->bIsVisited &&
        ((*Maze)[i + 1][j]->NumberRoom == -1 ||
         !(*Rooms)[(*Maze)[i + 1][j]->NumberRoom].bDoor))
        Neighbors.Push((*Maze)[i + 1][j]);

    if (j != 0 && !(*Maze)[i][j - 1]->bIsVisited &&
        ((*Maze)[i][j - 1]->NumberRoom == -1 ||
         !(*Rooms)[(*Maze)[i][j - 1]->NumberRoom].bDoor))
        Neighbors.Push((*Maze)[i][j - 1]);

    if (j != (Length - 1) && !(*Maze)[i][j + 1]->bIsVisited &&
        ((*Maze)[i][j + 1]->NumberRoom == -1 ||
         !(*Rooms)[(*Maze)[i][j + 1]->NumberRoom].bDoor))
        Neighbors.Push((*Maze)[i][j + 1]);
}

bool MazeGenerationCreation::CheckNearbyRoom(int Row, int Column, int RoomSize) {
    bool NeighBoardRoom = false;
    bool Left = true;
    bool Right = true;
    bool Top = true;
    bool Bot = true;

    // TopCheck
    if (Row != 0) {
        NeighBoardRoom = CheckNearbyRoomWrapper(Row - 1, Column, RoomSize, 0);
        if (NeighBoardRoom) return true;
    } else
        Top = false;

    // LeftCheck
    if (Column != 0) {
        NeighBoardRoom = CheckNearbyRoomWrapper(Row, Column - 1, RoomSize, 1);
        if (NeighBoardRoom) return true;
    } else
        Left = false;

    // BotCheck
    if (Row < Length - 2) {
        NeighBoardRoom = CheckNearbyRoomWrapper(Row + 2, Column, RoomSize, 2);
        if (NeighBoardRoom) return true;
    } else
        Bot = false;

    // RightCheck
    if (Column < Length - 2) {
        NeighBoardRoom = CheckNearbyRoomWrapper(Row, Column + 2, RoomSize, 3);
        if (NeighBoardRoom) return true;
    } else
        Right = false;

    if (Top) {
        if (Left) {
            if ((*Maze)[Row - 1][Column - 1]->NumberRoom != -1 ||
                (*Maze)[Row - 1][Column - 1]->bIsObstacle)
                return true;
        }

        if (Right) {
            if ((*Maze)[Row - 1][Column + RoomSize]->NumberRoom != -1 ||
                (*Maze)[Row - 1][Column + RoomSize]->bIsObstacle)
                return true;
        }
    }

    if (Bot) {
        if (Right) {
            if ((*Maze)[Row + RoomSize][Column + RoomSize]->NumberRoom != -1 ||
                (*Maze)[Row + RoomSize][Column + RoomSize]->bIsObstacle)
                return true;
        }
        if (Left) {
            if ((*Maze)[Row + RoomSize][Column - 1]->NumberRoom != -1 ||
                (*Maze)[Row + RoomSize][Column - 1]->bIsObstacle)
                return true;
        }
    }

    return false;
}

bool MazeGenerationCreation::CheckNearbyRoomWrapper(int Row, int Column,
                                                int RoomSize, int Side) {
    switch (Side) {
        case 0:

            for (int i = 0; i < RoomSize; i++) {
                if ((*Maze)[Row][Column + i]->NumberRoom != -1 ||
                    (*Maze)[Row][Column + i]->bIsObstacle)
                    return true;
            }
            break;

        case 1:

            for (int i = 0; i < RoomSize; i++) {
                if ((*Maze)[Row + i][Column]->NumberRoom != -1 ||
                    (*Maze)[Row + i][Column]->bIsObstacle)
                    return true;
            }
            break;

        case 2:

            for (int i = 0; i < RoomSize; i++) {
                if ((*Maze)[Row][Column + i]->NumberRoom != -1 ||
                    (*Maze)[Row][Column + i]->bIsObstacle)
                    return true;
            }
            break;

        case 3:

            for (int i = 0; i < RoomSize; i++) {
                if ((*Maze)[Row + i][Column]->NumberRoom != -1 ||
                    (*Maze)[Row + i][Column]->bIsObstacle)
                    return true;
            }
            break;

        default:
            break;
    }

    return false;
}

void MazeGenerationCreation::RoomWallHide(TArray<AMazeCell*>& Room, int rowExtr,
                                      int columnExtr, int Pos) {
    int FirstIndice;
    int SecondIndice;

    for (int i = 0; i < 2; i++) {
        SecondIndice = i == 0 ? 3 : 1;
        for (int j = 0; j < 2; j++) {
            FirstIndice = (j + 1) * 2;
            (*Maze)[rowExtr + i][columnExtr + j]->NumberRoom = Pos;
            (*Maze)[rowExtr + i][columnExtr + j]->HideWall(FirstIndice);
            (*Maze)[rowExtr + i][columnExtr + j]->HideWall(SecondIndice);
            Room.Add((*Maze)[rowExtr + i][columnExtr + j]);
        }
    }
}


