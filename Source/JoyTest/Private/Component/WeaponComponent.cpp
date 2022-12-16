// JoyTest Game

#include "Component/WeaponComponent.h"
#include "Weapons/BaseWeapon.h"
#include "Gameframework/Character.h"

UWeaponComponent::UWeaponComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UWeaponComponent::BeginPlay()
{
    Super::BeginPlay();

    //SpawnWeapon();
}

void UWeaponComponent::SpawnWeapon(TSubclassOf<ABaseWeapon> WeaponClass)
{
    ACharacter *Character = Cast<ACharacter>(GetOwner());
    if (!Character)
        return;

    if (!GetWorld())
        return;

    CurrentWeapon = GetWorld()->SpawnActor<ABaseWeapon>(WeaponClass);
    if (!CurrentWeapon)
        return;

    FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
    CurrentWeapon->AttachToComponent(Character->GetMesh(), AttachmentRules, SocketName);
    CurrentWeapon->SetOwner(Character);
}

void UWeaponComponent::DestoryWeapon()
{
    if (!CurrentWeapon)
        return;

    CurrentWeapon->Destroy();
}

void UWeaponComponent::Fire()
{
    if (!CurrentWeapon)
        return;

    CurrentWeapon->Fire();
}