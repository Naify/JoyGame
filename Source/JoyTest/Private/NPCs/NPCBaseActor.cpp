// JoyTest Game

#include "NPCs/NPCBaseActor.h"
#include "Component/HealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"

ANPCBaseActor::ANPCBaseActor()
{
    PrimaryActorTick.bCanEverTick = true;

    CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>("CollisionComponent");
    SetRootComponent(CollisionComponent);

    MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("MeshComponent");
    MeshComponent->SetupAttachment(CollisionComponent);

    TextComponent = CreateDefaultSubobject<UTextRenderComponent>("TextComponent");
    TextComponent->SetupAttachment(CollisionComponent);

    HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
}

void ANPCBaseActor::BeginPlay()
{
    Super::BeginPlay();

    if (HealthComponent)
    {
        OnHealthChanged(HealthComponent->GetHealth());
        HealthComponent->OnHealthChanged.AddUObject(this, &ANPCBaseActor::OnHealthChanged);
    }
}

void ANPCBaseActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ANPCBaseActor::OnHealthChanged(float Health)
{
    TextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}
