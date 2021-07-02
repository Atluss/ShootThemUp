// Shoot Them Up Game. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBaseWeapon.generated.h"

class USkeletalMeshComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ASTUBaseWeapon();

    virtual void StartFire();
    virtual void StopFire();

protected:

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
    USkeletalMeshComponent* WeaponMesh;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    float TraceMaxDistance = 1500.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    float DamageAmount = 10.0f;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    FName MuzzleSocketName = "MuzzleSocket";
    
	virtual void BeginPlay() override;

    virtual void MakeShot();
    virtual bool GetTraceData(FVector&, FVector&) const;

    APlayerController* GetPlayerController() const;
    bool GetPlayerViewPoint(FVector&, FRotator&) const;
    FVector GetMuzzleWorldLocation() const;
    void MakeHit(FHitResult&, FVector&, FVector&);

    void MakeDamage(const FHitResult&);
};
