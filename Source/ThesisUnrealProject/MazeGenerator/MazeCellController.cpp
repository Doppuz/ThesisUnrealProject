// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeCellController.h"

MazeCellController::MazeCellController()
{
}

MazeCellController::~MazeCellController()
{
}

FString MazeCellController::PrintCell() {
    if(IsObstacle)
        return "4";
    return "0";
    
}
