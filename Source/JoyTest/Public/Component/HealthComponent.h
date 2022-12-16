// JoyTest Game

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "HealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnDamageReceived, float)

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class JOYTEST_API UHealthComponent : public UActorComponent
{
    GENERATED_BODY()

  public:
    UHealthComponent();

    float GetHealth() const  {return Health;}

    UFUNCTION(BlueprintCallable)
    bool IsDead() const { return Health <= 0.0f; }

    UFUNCTION(BlueprintCallable, Category = "Health")
    float GetHealthPercent() const { return Health / MaxHealth; }

    bool TryToAddHealth( float HealthAmount );
    bool IsHealthFull() const;

    FOnDeath OnDeath;
    FOnHealthChanged OnHealthChanged;
    FOnHealthChanged OnDamageReceived;

  protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0.0", ClampMax = "500.0"))
    float MaxHealth = 100.0f;

    virtual void BeginPlay() override;

  private:
    float Health = 0.0f;

    void SetHealth(float NewHealth);

    UFUNCTION()
    void OnTakeAnyDamage(AActor *DamagedActor, float Damage, const class UDamageType *DamageType,
                         class AController *InstigatedBy, AActor *DamageCauser);
};
