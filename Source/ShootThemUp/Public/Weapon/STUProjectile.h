// Shoot Them Up Game. All rights reserved.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "STUProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class USTUWeaponFXComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUProjectile : public AActor
{
	GENERATED_BODY()
	
public:
	ASTUProjectile();

    void SetShotDirection(const FVector& Direction){ ShotDirection = Direction; };

protected:

    UPROPERTY(VisibleAnywhere, Category="Weapone")
    USphereComponent* CollisionComponent;

    UPROPERTY(VisibleAnywhere, Category="Weapone")
    UProjectileMovementComponent* MovementComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapone")
    float DamageRadius = 200.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapone")
    float DamageAmount = 50.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapone")
    bool DoFullDamage = false;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapone")
    float LifeSeconds = 5.0f;

    UPROPERTY(VisibleAnywhere, Category="VFX")
    USTUWeaponFXComponent* WeaponFXComponent;
    
	virtual void BeginPlay() override;

private:
    FVector ShotDirection;

    UFUNCTION()
    void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

    AController* GetController() const;
};