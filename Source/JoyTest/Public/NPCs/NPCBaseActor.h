// JoyTest Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NPCBaseActor.generated.h"

class UHealthComponent;
class UTextRenderComponent;
class UCapsuleComponent;
class USkeletalMeshComponent;

UCLASS()
class JOYTEST_API ANPCBaseActor : public AActor
{
    GENERATED_BODY()

  public:
    ANPCBaseActor();

  protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCapsuleComponent *CollisionComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent *MeshComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UHealthComponent *HealthComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UTextRenderComponent *TextComponent;

  public:
    virtual void Tick(float DeltaTime) override;

  private:
    void OnHealthChanged(float Health);
};
