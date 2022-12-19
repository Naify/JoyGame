// JoyTest Game


#include "Player/ReloadAnimNotify.h"

void UReloadAnimNotify::Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation)
{
    OnNotified.Broadcast();
    Super::Notify(MeshComp, Animation);
}