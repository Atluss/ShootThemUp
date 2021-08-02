// Shoot Them Up Game. All rights reserved.


#include "AI/Services/STUChangeWeaponService.h"
#include "AIController.h"
#include "STUUtils.h"
#include "STUWeaponComponent.h"

USTUChangeWeaponService::USTUChangeWeaponService()
{
    NodeName = "Change weapon";
}

void USTUChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    const auto Controller = OwnerComp.GetAIOwner();
    if (Controller)
    {
        const auto WeaponController = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(Controller->GetPawn());
        if (WeaponController && Probability > 0 && FMath::FRand() <= Probability)
        {
            WeaponController->NextWeapon();
        }
    }

    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
