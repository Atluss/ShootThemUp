// Shoot Them Up Game. All rights reserved.


#include "Components/STURespawnComponent.h"
#include "STUGameModeBase.h"


USTURespawnComponent::USTURespawnComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USTURespawnComponent::Respawn(int32 RespawnTime)
{
    if (!GetWorld()) return;
    RespawnCountDown = RespawnTime;
    GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &USTURespawnComponent::RespawnTimerUpdate, 1.0f, true);
}

bool USTURespawnComponent::IsRespawnInProgress() const
{
    return GetWorld()->GetTimerManager().IsTimerActive(RespawnTimerHandle);
}

void USTURespawnComponent::RespawnTimerUpdate()
{
    if (--RespawnCountDown == 0)
    {
        if (!GetWorld()) return;
        GetWorld()->GetTimerManager().ClearTimer(RespawnTimerHandle);

        const auto GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
        if (!GameMode) return;

        GameMode->RespawnRequest(Cast<AController>(GetOwner()));
    }
}


