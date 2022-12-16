// JoyTest Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VoidZoneActor.generated.h"

UCLASS()
class JOYTEST_API AVoidZoneActor : public AActor
{
    GENERATED_BODY()

  public:
    AVoidZoneActor();

  protected:
    virtual void BeginPlay() override;

  public:
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    USceneComponent *SceneComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Radius = 300.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Damage = 5.0f;
};
