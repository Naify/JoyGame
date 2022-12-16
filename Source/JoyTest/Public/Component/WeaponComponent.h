// JoyTest Game

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

class ABaseWeapon;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class JOYTEST_API UWeaponComponent : public UActorComponent
{
    GENERATED_BODY()

  public:
    UWeaponComponent();

    void Fire();

  protected:
    virtual void BeginPlay() override;

    /*UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TSubclassOf<ABaseWeapon> WeaponClass;*/

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName SocketName = "WeaponSocket";
    
    UFUNCTION(BlueprintCallable, Category = "Weapon")
    void SpawnWeapon(TSubclassOf<ABaseWeapon> WeaponClass);

    UFUNCTION(BlueprintCallable, Category = "Weapon")
    void DestoryWeapon();

  private:
    UPROPERTY()
    ABaseWeapon *CurrentWeapon = nullptr;
};
