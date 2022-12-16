// JoyTest Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePickupActor.generated.h"

class USphereComponent;

UCLASS()
class JOYTEST_API ABasePickupActor : public AActor
{
    GENERATED_BODY()

  public:
    ABasePickupActor();

  protected:
    UPROPERTY(VisibleAnywhere, Category = "Pickup")
    USphereComponent *Collision;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
    float RespawnTime = 5.0f;

    UFUNCTION(BlueprintCallable, Category = "Pickup")
    void PickupWasTaken();

    virtual void BeginPlay() override;
    virtual void NotifyActorBeginOverlap(AActor *OtherActor) override;

  public:
    virtual void Tick(float DeltaTime) override;

  private:
    virtual bool GivePickupTo(APawn *PlayerPawn);

    void Respawn();
};
