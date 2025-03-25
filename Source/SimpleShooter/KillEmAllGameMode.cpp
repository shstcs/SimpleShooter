// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"



void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
    APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
    if(PlayerController != nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("Player Dead"));
        EndGame(false);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Pawn Dead"));
    }

    for(AShooterAIController* Controller : TActorRange<AShooterAIController>(GetWorld()))     //월드 내의 모든 컨트롤러를 가져옴
    {
        if(!Controller->IsDead())
        {
            return;
        }
    }

    EndGame(true);
}

void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner)
{
    
    for(AController* Controller : TActorRange<AController>(GetWorld()))     //월드 내의 모든 컨트롤러를 가져옴
    {
        bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
        Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
    }
}