// JoyTest Game

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "Structs.h"
#include "PlayerWidget.generated.h"

UCLASS()
class JOYTEST_API UPlayerWidget : public UUserWidget
{
    GENERATED_BODY()

  public:
    UFUNCTION(BlueprintCallable, Category = "UI")
    float GetHealth() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetWeaponAmmo(FAmmo &Ammo) const;
};
