// Shoot Them Up Game. All rights reserved.


#include "AI/Services/STUFireService.h"

#include "AIController.h"
#include "STUUtils.h"
#include "STUWeaponComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

USTUFireService::USTUFireService()
{
    NodeName = "Fire";
}

void USTUFireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    const auto Controller = OwnerComp.GetAIOwner();
    const auto BlackBoard = OwnerComp.GetBlackboardComponent();

    const auto HasAim = BlackBoard && BlackBoard->GetValueAsObject(EnemyActorKey.SelectedKeyName);
    
    if (Controller)
    {
        const auto WeaponController = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(Controller->GetPawn());
        if (WeaponController)
        {
            HasAim ? WeaponController->StartFire() : WeaponController->StopFire();
        }
    }
    
    
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
