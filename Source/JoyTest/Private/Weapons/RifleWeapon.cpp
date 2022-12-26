// JoyTest Game


#include "Weapons/RifleWeapon.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"

ARifleWeapon::ARifleWeapon()
{
}

void ARifleWeapon::Fire()
{
    const auto Player = Cast<ACharacter>(GetOwner());
    if (!Player || IsAllAmmoEmpty())
        return;

    const auto Controller = Player->GetController<APlayerController>();
    if (!Controller)
        return;

    FVector ViewLocation;
    FRotator ViewRotation;
    Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);

    if (!WeaponMesh)
        return;

    const FTransform SocketTransform = WeaponMesh->GetSocketTransform(SocketName);
    const FVector TraceStart = ViewLocation; // for VR start can be from muzzle - SocketTransform.GetLocation();
    //const FVector ShootDirection = ViewRotation.Vector(); // SocketTransform.GetRotation().GetForwardVector();
    const auto HalfRad = FMath::DegreesToRadians(Spread);
    const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad);
    const FVector TraceEnd = TraceStart + ShootDirection * TraceDistance;

    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(GetOwner());

    if (!GetWorld())
        return;

    FHitResult HitResult;
    GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility,
                                         CollisionParams);

    if (HitResult.bBlockingHit)
    {
        MakeDamage(HitResult);
        DrawDebugLine(GetWorld(), SocketTransform.GetLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.0f, 0,
                      3.0f);
        DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24, FColor::Red, false, 5.0f);
    }
    else
    {
        DrawDebugLine(GetWorld(), SocketTransform.GetLocation(), TraceEnd, FColor::Red, false, 3.0f, 0, 3.0f);
    }

    DecreaseAmmo();
}

void ARifleWeapon::MakeDamage(const FHitResult &HitResult)
{
    const auto DamagedActor = HitResult.GetActor();
    if (!DamagedActor)
        return;

    const auto Player = Cast<ACharacter>(GetOwner());
    if (!Player)
        return;

    const auto Controller = Player->GetController<APlayerController>();
    if (!Controller)
        return;

    DamagedActor->TakeDamage(DamageToHealth, FDamageEvent(), Controller, this);
}