// JoyTest Game

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Structs.h"
#include "WeaponComponent.generated.h"

class ABaseWeapon;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class JOYTEST_API UWeaponComponent : public UActorComponent
{
    GENERATED_BODY()

  public:
    UWeaponComponent();

    void Fire();
    void Reload();

    bool GetWeaponCurrentAmmo(FAmmo &Ammo) const;

  protected:
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName SocketName = "WeaponSocket";
    
    UFUNCTION(BlueprintCallable, Category = "Weapon")
    void SpawnWeapon(TSubclassOf<ABaseWeapon> Weapon, UAnimMontage *Reload);

    UFUNCTION(BlueprintCallable, Category = "Weapon")
    void DestoryWeapon();

  private:
    UPROPERTY()
    ABaseWeapon *Weapon = nullptr;

    UPROPERTY()
    UAnimMontage *ReloadAnimMontage = nullptr;

    void InitAnim();
    bool ReloadAnimInProgress = false;
    void OnReloadFinished();
    bool CanReload() const;

    void OnEmptyClip();
    void ChangeClip();
};
