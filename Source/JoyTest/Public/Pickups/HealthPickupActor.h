// JoyTest Game

#pragma once

#include "CoreMinimal.h"
#include "Pickups/BasePickupActor.h"
#include "HealthPickupActor.generated.h"

/**
 *
 */
UCLASS()
class JOYTEST_API AHealthPickupActor : public ABasePickupActor
{
    GENERATED_BODY()

  protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1.0", ClampMax = "100.0"))
    float HealthAmount = 100.0f;

  private:
    virtual bool GivePickupTo(APawn *PlayerPawn) override;
};
