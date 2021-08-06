// Shoot Them Up Game. All rights reserved.

#pragma once

#include "CoreMinimal.h"

#include "STUBaseWeapon.h"
#include "Components/ActorComponent.h"
#include "STUCoreTypes.h"
#include "STUWeaponComponent.generated.h"

class ASTUBaseWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API USTUWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USTUWeaponComponent();

    virtual void StartFire();
    virtual void NextWeapon();

    void StopFire();
    void Reload();

    bool GetCurrentWeaponUIData(FWeaponUIData&) const;
    bool GetCurrentWeaponAmmoData(FAmmoData&) const;

    bool TryToAddAmmo(TSubclassOf<ASTUBaseWeapon>, int32);

    bool NeedAmmo(TSubclassOf<ASTUBaseWeapon>) const;

protected:

    UPROPERTY(EditDefaultsOnly, Category="Weapon")
    TArray<FWeaponData> WeaponData;
    
    UPROPERTY(EditDefaultsOnly, Category="Weapon")
    TArray<TSubclassOf<ASTUBaseWeapon>> WeaponClasses;

    UPROPERTY(EditDefaultsOnly, Category="Weapon")
    FName WeaponEquipSocketName = "WeaponSocket";

    UPROPERTY(EditDefaultsOnly, Category="Weapon")
    FName WeaponArmorySocketName = "ArmorySocket";
    
    UPROPERTY(EditDefaultsOnly, Category="Animation")
    UAnimMontage* EquipAnimMontage;

    UPROPERTY()
    ASTUBaseWeapon* CurrentWeapon = nullptr;

    UPROPERTY()
    TArray<ASTUBaseWeapon*> Weapons;

    int32 CurrentWeaponIndex = 0;
    
	virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    bool CanFire() const;
    bool CanEquip() const;
    void EquipWeapon(int32 IndexWeapon);

private:
    UPROPERTY()
    UAnimMontage* CurrentReloadAnimMontage = nullptr;

    bool EquipAnimInProgress = false;
    bool ReloadAnimInProgress = false;
    
    void SpawnWeapons();
    void AttachWeaponToSocket(ASTUBaseWeapon*, USceneComponent*, const FName&);

    void PlayAnimMontage(UAnimMontage*);
    void InitAnimations();
    
    void OnEquipFinished(USkeletalMeshComponent* MeshComp);
    void OnReloadFinished(USkeletalMeshComponent* MeshComp);

    bool CanReload() const;

    void OnEmptyClip(ASTUBaseWeapon* AmmoEmptyWeapon);
    void ChangeClip();
};
