// JoyTest Game


#include "Pickups/HealthPickupActor.h"
#include "Component/HealthComponent.h"

bool AHealthPickupActor::GivePickupTo(APawn *PlayerPawn)
{
     if (!PlayerPawn)
         return false;

    const auto Component = PlayerPawn->GetComponentByClass(UHealthComponent::StaticClass());

    const auto HealthComponent = Cast<UHealthComponent>(Component);
    if (!HealthComponent)
        return false;

    return HealthComponent->TryToAddHealth(HealthAmount);
}