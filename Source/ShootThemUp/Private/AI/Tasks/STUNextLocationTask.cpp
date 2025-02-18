// Shoot Them Up Game. All Rights Reserved.

#include "AI/Tasks/STUNextLocationTask.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"

USTUNextLocationTask::USTUNextLocationTask()
{
    NodeName = "NextLocation";
}

EBTNodeResult::Type USTUNextLocationTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    const auto Controller = OwnerComp.GetAIOwner();
    const auto Blackboard = OwnerComp.GetBlackboardComponent();
    if (!Controller || !Blackboard) return EBTNodeResult::Type::Failed;

    const auto Pawn = Controller->GetPawn();
    if (!Pawn) return EBTNodeResult::Type::Failed;

    const auto NavSys = UNavigationSystemV1::GetCurrent(Pawn);
    if (!NavSys) return EBTNodeResult::Type::Failed;

    auto Location = Pawn->GetActorLocation();
    if (!bSelfCenter)
    {
        auto CenterActor = Cast<AActor>(Blackboard->GetValueAsObject(CenterActorKey.SelectedKeyName));
        if (!CenterActor) return EBTNodeResult::Type::Failed;
        Location = CenterActor->GetActorLocation();
    }

    FNavLocation ResultLocation;
    if (NavSys->GetRandomReachablePointInRadius(Location, MoveRaidus, ResultLocation))
    {
        Blackboard->SetValueAsVector(AimLocationKey.SelectedKeyName, ResultLocation.Location);
        return EBTNodeResult::Type::Succeeded;
    }
    else
        return EBTNodeResult::Type::Failed;
}