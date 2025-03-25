// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_playerLocationIfSeen.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "GameFramework/Pawn.h"


UBTService_playerLocationIfSeen::UBTService_playerLocationIfSeen()
{
    NodeName = TEXT("Update Player Location If Seen");
}

void UBTService_playerLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    auto BlackboardComp = OwnerComp.GetBlackboardComponent();
    if(BlackboardComp == nullptr) return;

    auto Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if(Player == nullptr) return;

    if(OwnerComp.GetAIOwner() == nullptr) return;

    if(OwnerComp.GetAIOwner()->LineOfSightTo(Player))
    {
        BlackboardComp->SetValueAsObject(GetSelectedBlackboardKey(), Player);
    }
    else
    {
        BlackboardComp->ClearValue(GetSelectedBlackboardKey());
    }
}