// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeCellController.h"

MazeCellController::MazeCellController(int PosX, int PosY):
    PosX{PosX},PosY{PosY}{

}

MazeCellController::~MazeCellController()
{
}

FString MazeCellController::PrintCell() {
    //if(IsObstacle)
    //    return "4";
    FString b = LeftWall == true ? " Left " : " ";
    FString c = RightWall == true ? " Right " : " ";
    FString d = UpWall == true ? " Up " : " ";
    FString e = DownWall == true ? " Down " : " ";
    FString f = " | ";
    return b+c+d+e+f;
    
}
