// JoyTest Game

#pragma once

#include "CoreMinimal.h"
#include "Weapons/BaseWeapon.h"
#include "RifleWeapon.generated.h"

/**
 *
 */
UCLASS()
class JOYTEST_API ARifleWeapon : public ABaseWeapon
{
    GENERATED_BODY()

  public:
    ARifleWeapon();

    void Fire();

    void MakeDamage(const FHitResult &HitResult);
};
