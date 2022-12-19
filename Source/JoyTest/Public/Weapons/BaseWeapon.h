// JoyTest Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnClipEmpty);

class USkeletalMeshComponent;

USTRUCT(BlueprintType)
struct FAmmo
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    int32 Bullets;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    int32 Clips;
};

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

    virtual void MakeDamage(const FHitResult &HitResult);

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    FAmmo DefaultAmmo {5, 2};

    void DecreaseAmmo();
    
    bool IsClipEmpty() const;

  private:
    FAmmo CurrentAmmo;
};
