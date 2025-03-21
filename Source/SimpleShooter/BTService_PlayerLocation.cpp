// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"

UBTService_PlayerLocation::UBTService_PlayerLocation()
{
    NodeName = TEXT("Update Player Location");
}

void UBTService_PlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    auto BlackboardComp = OwnerComp.GetBlackboardComponent();
    if(BlackboardComp == nullptr) return;

    auto Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if(Player == nullptr) return;

    BlackboardComp->SetValueAsVector(GetSelectedBlackboardKey(), Player->GetActorLocation());
}