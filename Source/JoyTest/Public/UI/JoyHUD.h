// JoyTest Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "JoyHUD.generated.h"

UCLASS()
class JOYTEST_API AJoyHUD : public AHUD
{
    GENERATED_BODY()

  protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

    virtual void BeginPlay() override;
};
