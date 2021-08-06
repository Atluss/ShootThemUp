// Shoot Them Up Game. All rights reserved.


#include "AI/EQS/EnvEnvQueryTest_PickupCouldTaken.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_ActorBase.h"
#include "Pickups/STUBasePickup.h"

UEnvEnvQueryTest_PickupCouldTaken::UEnvEnvQueryTest_PickupCouldTaken(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
    Cost = EEnvTestCost::Low;
    ValidItemType = UEnvQueryItemType_ActorBase::StaticClass();
    SetWorkOnFloatValues(false);
}

void UEnvEnvQueryTest_PickupCouldTaken::RunTest(FEnvQueryInstance& QueryInstance) const
{
    const auto DataOwner = QueryInstance.Owner.Get();
    BoolValue.BindData(DataOwner, QueryInstance.QueryID);
    const bool WantsBeTakable = BoolValue.GetValue();
    
    for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
    {
        const auto ItemActor = GetItemActor(QueryInstance, It.GetIndex());
        const auto PickupActor = Cast<ASTUBasePickup>(ItemActor);
        if (!PickupActor) continue;

        const auto CouldBeTaken = PickupActor->CouldBeTaken();
        It.SetScore(TestPurpose, FilterType, CouldBeTaken, WantsBeTakable);
    }
}
