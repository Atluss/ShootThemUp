// Shoot Them Up Game. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STURifleWeapon.generated.h"

class USTUWeaponFXComponent;
class UNiagaraSystem;
class UNiagaraComponent;
class UAudioComponent;

UCLASS()
class SHOOTTHEMUP_API ASTURifleWeapon : public ASTUBaseWeapon
{
	GENERATED_BODY()

public:
    ASTURifleWeapon();

    virtual void StartFire() override;
    virtual void StopFire() override;

protected:

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float TimeBetweenShots = 0.1f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float BulletSpread = 1.5f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float DamageAmount = 10.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX")
    UNiagaraSystem* TraceFX;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX")
    FString TraceTargetName = "TraceTarget";
    
    UPROPERTY(VisibleAnywhere, Category="VFX")
    USTUWeaponFXComponent* WeaponFXComponent;

    virtual void BeginPlay() override;
    virtual void MakeShot() override;
    virtual bool GetTraceData(FVector&, FVector&) const;

private:
    FTimerHandle ShotTimerHandle;

    UPROPERTY()
    UNiagaraComponent* MuzzleFXComponent;

    UPROPERTY()
    UAudioComponent* FireAuditComponent;
    
    void MakeDamage(const FHitResult&);
    void InitFX();
    void SetFXActive(bool IsActive);

    void SpawnTraceFX(const FVector& StartTrace, const FVector& TraceEnd);

    AController* GetController() const;
};
