// Fill out your copyright notice in the Description page of Project Settings.


#include "KoEGameMode.h"
#include "../Player/KoEPlayerController.h"
#include "../Player/KoEPlayerCharacter.h"
#include "../UI/KoEHUD.h"
#include "KoEGameState.h"
#include "KoEPlayerState.h"

AKoEGameMode::AKoEGameMode()
{
    PlayerControllerClass = AKoEPlayerController::StaticClass();
    DefaultPawnClass = AKoEPlayerCharacter::StaticClass();     // top-down pawn below
    HUDClass = AKoEHUD::StaticClass();
    GameStateClass = AKoEGameState::StaticClass();
    PlayerStateClass = AKoEPlayerState::StaticClass();
}
