// JoyTest Game

#pragma once

#include "Animation/AnimNotifies/AnimNotify.h"
#include "CoreMinimal.h"
#include "ReloadAnimNotify.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnNotifiedSignature);

UCLASS()
class JOYTEST_API UReloadAnimNotify : public UAnimNotify
{
    GENERATED_BODY()

  public:
    virtual void Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation) override;

    FOnNotifiedSignature OnNotified;
};
