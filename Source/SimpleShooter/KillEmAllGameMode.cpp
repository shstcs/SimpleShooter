// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"


void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
    APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
    if(PlayerController != nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("Pawn Alive"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Pawn Dead"));
    }
}