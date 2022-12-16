// JoyTest Game

#pragma once

#include "CoreMinimal.h"
#include "Pickups/BasePickupActor.h"
#include "AmmoPickupActor.generated.h"

/**
 *
 */
UCLASS()
class JOYTEST_API AAmmoPickupActor : public ABasePickupActor
{
    GENERATED_BODY()

  private:
    virtual bool GivePickupTo(APawn *PlayerPawn) override;
};
