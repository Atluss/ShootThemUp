// Shoot Them Up Game. All rights reserved.


#include "Weapon/STURifleWeapon.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Weapon/Components/STUWeaponFXComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"

ASTURifleWeapon::ASTURifleWeapon()
{
    WeaponFXComponent = CreateDefaultSubobject<USTUWeaponFXComponent>("STUWeaponFXComponent");
}

void ASTURifleWeapon::BeginPlay()
{
    Super::BeginPlay();
    check(WeaponFXComponent);
}

void ASTURifleWeapon::StartFire()
{
    InitFX();
    GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ASTURifleWeapon::MakeShot, TimeBetweenShots, true);
    MakeShot();
}

void ASTURifleWeapon::StopFire()
{
    GetWorldTimerManager().ClearTimer(ShotTimerHandle);
    SetFXActive(false);
}

void ASTURifleWeapon::Zoom(bool bEnabled)
{
    const auto Controller = Cast<APlayerController>(GetController());
    if (!Controller || !Controller->PlayerCameraManager) return;

    if (bEnabled)
    {
        DefaultCameraFOV = Controller->PlayerCameraManager->GetFOVAngle();
    }
    
    Controller->PlayerCameraManager->SetFOV(bEnabled ? FOVZoomAngle : DefaultCameraFOV);
}

void ASTURifleWeapon::MakeShot()
{
    if (!GetWorld() || IsAmmoEmpty())
    {
        StopFire();
        return;
    }

    FVector TraceStart;
    FVector TraceEnd;

    if (!GetTraceData(TraceStart, TraceEnd))
    {
        StopFire();
        return;
    }

    FHitResult HitResult;

    MakeHit(HitResult, TraceStart, TraceEnd);

    FVector TraceFXEnd = TraceEnd;
    if (HitResult.bBlockingHit)
    {
        TraceEnd = HitResult.ImpactPoint;
        MakeDamage(HitResult);
        WeaponFXComponent->PlayImpactFX(HitResult);
    }

    SpawnTraceFX(GetMuzzleWorldLocation(), TraceEnd);
    
    DecreaseAmmo();
}

bool ASTURifleWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
    FVector ViewLocation;
    FRotator ViewRotation;

    if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

    TraceStart = ViewLocation;

    const auto HalfRad = FMath::DegreesToRadians(BulletSpread);
    
    const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad);
    TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;

    return true;
}

void ASTURifleWeapon::MakeDamage(const FHitResult& HitResult)
{
    const auto DamageActor = HitResult.GetActor();
    if (!DamageActor) return;

    FPointDamageEvent PointDamageEvent;
    PointDamageEvent.HitInfo = HitResult;
    DamageActor->TakeDamage(DamageAmount, PointDamageEvent, GetController(), this);
}

void ASTURifleWeapon::InitFX()
{
    if (!MuzzleFXComponent)
    {
        MuzzleFXComponent = SpawnMuzzleFX();
    }
    if (!FireAuditComponent)
    {
        FireAuditComponent = UGameplayStatics::SpawnSoundAttached(FireSound, WeaponMesh, MuzzleSocketName);
    }
    SetFXActive(true);
}

void ASTURifleWeapon::SetFXActive(bool IsActive)
{
    if(MuzzleFXComponent)
    {
        MuzzleFXComponent->SetPaused(!IsActive);
        MuzzleFXComponent->SetVisibility(IsActive, true);
    }

    if (FireAuditComponent)
    {
        FireAuditComponent->SetPaused(!IsActive);
    }
}

void ASTURifleWeapon::SpawnTraceFX(const FVector& StartTrace, const FVector& TraceEnd)
{
    const auto TraceFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TraceFX, StartTrace);
    if (TraceFXComponent)
    {
        TraceFXComponent->SetNiagaraVariableVec3(TraceTargetName, TraceEnd);
    }
}

AController* ASTURifleWeapon::GetController() const
{
    const auto Pawn = Cast<APawn>(GetOwner());
    return Pawn ? Pawn->GetController() : nullptr;
}