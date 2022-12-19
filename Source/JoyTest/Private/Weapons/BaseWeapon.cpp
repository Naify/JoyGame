// JoyTest Game

#include "Weapons/BaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Character.h"

ABaseWeapon::ABaseWeapon()
{
    PrimaryActorTick.bCanEverTick = false;

    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
    SetRootComponent(WeaponMesh);
}

void ABaseWeapon::BeginPlay()
{
    Super::BeginPlay();

    CurrentAmmo = DefaultAmmo;

}

void ABaseWeapon::Fire()
{
}

void ABaseWeapon::MakeDamage(const FHitResult &HitResult)
{
}

void ABaseWeapon::DecreaseAmmo()
{
    if (CurrentAmmo.Bullets == 0)
    {
        UE_LOG(LogTemp, Display, TEXT("No more bullets"));
        return;
    }

    CurrentAmmo.Bullets--;

    UE_LOG(LogTemp, Display, TEXT("Bullets: %d"), CurrentAmmo.Bullets);

    if (IsClipEmpty() && !IsAllAmmoEmpty())
    {
        OnClipEmpty.Broadcast();
        //ChangeClip();
    }
}

bool ABaseWeapon::IsAllAmmoEmpty() const
{
    return CurrentAmmo.Clips == 0 && IsClipEmpty();
}

bool ABaseWeapon::IsClipEmpty() const
{
    return CurrentAmmo.Bullets == 0;
}

void ABaseWeapon::ChangeClip()
{
    if (CurrentAmmo.Clips == 0)
    {
        UE_LOG(LogTemp, Display, TEXT("No more Clips =("));
        return;
    }

    UE_LOG(LogTemp, Display, TEXT("------Changing clip-------"));

    CurrentAmmo.Bullets = DefaultAmmo.Bullets;
    CurrentAmmo.Clips--;

    UE_LOG(LogTemp, Display, TEXT("Bullets: %d"), CurrentAmmo.Bullets);
    UE_LOG(LogTemp, Display, TEXT("Clips: %d"), CurrentAmmo.Clips);
}

bool ABaseWeapon::CanReload() const
{
    return CurrentAmmo.Bullets < DefaultAmmo.Bullets && CurrentAmmo.Clips > 0;
}
