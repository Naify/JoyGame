// JoyTest Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Structs.h"
#include "BaseWeapon.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnClipEmpty);

class USkeletalMeshComponent;

UCLASS()
class JOYTEST_API ABaseWeapon : public AActor
{
    GENERATED_BODY()

  public:
    ABaseWeapon();

    virtual void Fire();

    FOnClipEmpty OnClipEmpty;

    void ChangeClip();
    bool CanReload() const;
    bool IsAllAmmoEmpty() const;

    FAmmo GetCurrentAmo() const { return CurrentAmmo; }

  protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent *WeaponMesh;

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName SocketName = "MuzzleSocket";

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float TraceDistance = 1000.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float DamageToHealth = 10.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    FAmmo DefaultAmmo {5, 2};

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float Spread = 1.1f;

    virtual void MakeDamage(const FHitResult &HitResult);

    void DecreaseAmmo();
    
    bool IsClipEmpty() const;

  private:
    FAmmo CurrentAmmo;
};
