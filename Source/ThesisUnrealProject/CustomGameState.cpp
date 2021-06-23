// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomGameState.h"

ACustomGameState::ACustomGameState() {
    CoinNumber = 0;
    MapPercentage = 0;
    Types.Add(Type::Achiever, 50.f);
    Types.Add(Type::Killer, 50.f);
    Types.Add(Type::Socializer, 50.f);
    Types.Add(Type::Explorer, 50.f);
}
