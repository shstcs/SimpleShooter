// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

AShooterAIController::AShooterAIController()
{

}

void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();
    PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    // SetFocus(PlayerPawn);

    if(AIBehavior != nullptr)
    {
        RunBehaviorTree(AIBehavior);

        GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("AI Controller for %s is missing a behavior tree"), *GetName());
    }
    
}

void AShooterAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    // // if Line of Sight
    // if(LineOfSightTo(PlayerPawn))
    // {
    //     MoveToActor(PlayerPawn, AcceptanceRadius);
    //     SetFocus(PlayerPawn);
    //     // fire
    // }
    // else
    // {
    //     ClearFocus(EAIFocusPriority::Gameplay);
    //     // stop firing
    // }
}