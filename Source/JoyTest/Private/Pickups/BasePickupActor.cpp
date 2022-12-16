// JoyTest Game

#include "Pickups/BasePickupActor.h"
#include "Components/SphereComponent.h"

ABasePickupActor::ABasePickupActor()
{
    PrimaryActorTick.bCanEverTick = false;

    Collision = CreateDefaultSubobject<USphereComponent>("Collision");
    Collision->InitSphereRadius(50.0f);
    Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    Collision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    SetRootComponent(Collision);
}

void ABasePickupActor::BeginPlay()
{
    Super::BeginPlay();
}

void ABasePickupActor::NotifyActorBeginOverlap(AActor *OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

    const auto Pawn = Cast<APawn>(OtherActor);
    if (GivePickupTo(Pawn))
    {
        PickupWasTaken();
    }
}

void ABasePickupActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

bool ABasePickupActor::GivePickupTo(APawn *PlayerPawn)
{
    return false;
}

void ABasePickupActor::PickupWasTaken()
{
    if (Collision)
    {
        Collision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    }
    
    if (GetRootComponent())
    {
        GetRootComponent()->SetVisibility(false, true);
    }

    FTimerHandle RespawnTimerHandle;
    GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ABasePickupActor::Respawn, RespawnTime);
}

void ABasePickupActor::Respawn()
{
    if (Collision)
    {
        Collision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    }
    
    if (GetRootComponent())
    {
        GetRootComponent()->SetVisibility(true, true);
    }
}