// JoyTest Game


#include "UI/PlayerWidget.h"
#include "Component/HealthComponent.h"
#include "Component/WeaponComponent.h"

float UPlayerWidget::GetHealth() const
{
    const auto Player = GetOwningPlayerPawn();
    if (!Player)
        return 0.0f;

    const auto Component = Player->GetComponentByClass(UHealthComponent::StaticClass());
    const auto HealthComponent = Cast<UHealthComponent>(Component);
    if (!HealthComponent)
        return 0.0f;

    return HealthComponent->GetHealthPercent();
}

bool UPlayerWidget::GetWeaponAmmo(FAmmo &Ammo) const
{
    const auto Player = GetOwningPlayerPawn();
    if (!Player)
        return false;

    const auto Component = Player->GetComponentByClass(UWeaponComponent::StaticClass());
    const auto WeaponComponent = Cast<UWeaponComponent>(Component);
    if (!WeaponComponent)
        return false;

    return WeaponComponent->GetWeaponCurrentAmmo(Ammo);
}
