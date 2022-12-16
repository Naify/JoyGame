// JoyTest Game

#pragma once

#include "CoreMinimal.h"
#include "Weapons/BaseWeapon.h"
#include "SecondWeapon.generated.h"

/**
 *
 */
UCLASS()
class JOYTEST_API ASecondWeapon : public ABaseWeapon
{
    GENERATED_BODY()

  public:
    ASecondWeapon();

    void Fire();

    void MakeDamage(const FHitResult &HitResult);

  protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float DamageRadius = 50.0f;
};
