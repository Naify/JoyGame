// JoyTest Game

#include "Component/WeaponComponent.h"
#include "Weapons/BaseWeapon.h"
#include "Gameframework/Character.h"
#include "Player/ReloadAnimNotify.h"

UWeaponComponent::UWeaponComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UWeaponComponent::BeginPlay()
{
    Super::BeginPlay();

    //SpawnWeapon();
}

void UWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (!Weapon)
        return;

    Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
    Weapon->Destroy();
    Weapon = nullptr;   
    
    Super::EndPlay(EndPlayReason);
}

void UWeaponComponent::SpawnWeapon(TSubclassOf<ABaseWeapon> WeaponClass, UAnimMontage *Reload)
{
    ACharacter *Character = Cast<ACharacter>(GetOwner());
    if (!Character)
        return;

    if (!GetWorld())
        return;

    Weapon = GetWorld()->SpawnActor<ABaseWeapon>(WeaponClass);
    if (!Weapon)
        return;

    Weapon->OnClipEmpty.AddUObject(this, &UWeaponComponent::OnEmptyClip);

    FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
    Weapon->AttachToComponent(Character->GetMesh(), AttachmentRules, SocketName);
    Weapon->SetOwner(Character);

    ReloadAnimMontage = Reload ? Reload : nullptr;
    InitAnim();
}

void UWeaponComponent::DestoryWeapon()
{
    if (!Weapon)
        return;

    Weapon->Destroy();
    ReloadAnimMontage = nullptr;
}

void UWeaponComponent::OnReloadFinished()
{
    ReloadAnimInProgress = false;
}

bool UWeaponComponent::CanReload() const
{
    return Weapon && !ReloadAnimInProgress && Weapon->CanReload();
}

void UWeaponComponent::OnEmptyClip()
{
    ChangeClip();
}

void UWeaponComponent::ChangeClip()
{
    if (!ReloadAnimMontage || !CanReload())
        return;

    ACharacter *Character = Cast<ACharacter>(GetOwner());
    if (!Character)
        return;

    ReloadAnimInProgress = true;
    Weapon->ChangeClip();
    Character->PlayAnimMontage(ReloadAnimMontage);
}

void UWeaponComponent::Fire()
{
    if (!Weapon || ReloadAnimInProgress || Weapon->IsAllAmmoEmpty())
        return;

    Weapon->Fire();
}

void UWeaponComponent::Reload()
{
    ChangeClip();
}

bool UWeaponComponent::GetWeaponCurrentAmmo(FAmmo& Ammo) const
{
    if (Weapon)
    {
        Ammo = Weapon->GetCurrentAmo();
        return true;
    }
    return false;
}

bool UWeaponComponent::HaveWeapon() const
{
    if (!Weapon)
        return false;
    return true;
}

void UWeaponComponent::InitAnim()
{
    if (!ReloadAnimMontage)
        return;

    const auto NotifyEvents = ReloadAnimMontage->Notifies;
    for (auto NotifyEvent : NotifyEvents)
    {
        auto ReloadNotify = Cast<UReloadAnimNotify>(NotifyEvent.Notify);
        if (ReloadNotify)
        {
            ReloadNotify->OnNotified.AddUObject(this, &UWeaponComponent::OnReloadFinished);
            break;
        }
    }
}