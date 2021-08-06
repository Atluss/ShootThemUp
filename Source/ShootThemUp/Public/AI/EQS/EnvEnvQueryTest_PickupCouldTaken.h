// Shoot Them Up Game. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EnvEnvQueryTest_PickupCouldTaken.generated.h"

UCLASS()
class SHOOTTHEMUP_API UEnvEnvQueryTest_PickupCouldTaken : public UEnvQueryTest
{
	GENERATED_BODY()

public:
    UEnvEnvQueryTest_PickupCouldTaken(const FObjectInitializer& ObjectInitializer);
    virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;
};
