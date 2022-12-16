// JoyTest Game

#include "Player/JoyCharacter.h"
#include "Camera/CameraComponent.h"
#include "Component/HealthComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/TextRenderComponent.h"
#include "Component/WeaponComponent.h"

AJoyCharacter::AJoyCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;
    SpringArmComponent->SocketOffset = FVector(0.f, 100.f, 80.f);

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);

    HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");

    TextComponent = CreateDefaultSubobject<UTextRenderComponent>("TextComponent");
    TextComponent->SetupAttachment(GetRootComponent());
    TextComponent->SetOwnerNoSee(true);

    WeaponComponent = CreateDefaultSubobject<UWeaponComponent>("WeaponComponent");

    DeathAnimMontage = nullptr;
}

void AJoyCharacter::BeginPlay()
{
    Super::BeginPlay();

    if (HealthComponent)
    {
        OnHealthChanged(HealthComponent->GetHealth());
        HealthComponent->OnDeath.AddUObject(this, &AJoyCharacter::OnDeath);
        HealthComponent->OnHealthChanged.AddUObject(this, &AJoyCharacter::OnHealthChanged);
    }
}

void AJoyCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AJoyCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &AJoyCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AJoyCharacter::MoveRight);
    PlayerInputComponent->BindAxis("LookUp", this, &AJoyCharacter::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("Turn", this, &AJoyCharacter::AddControllerYawInput);
    PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &UWeaponComponent::Fire);
}

void AJoyCharacter::MoveForward(float Amount)
{
    AddMovementInput(GetActorForwardVector(), Amount);
}

void AJoyCharacter::MoveRight(float Amount)
{
    AddMovementInput(GetActorRightVector(), Amount);
}

void AJoyCharacter::OnDeath()
{
    //UE_LOG(LogTemp, Display, TEXT("Player is dead"));

    PlayAnimMontage(DeathAnimMontage);
    GetCharacterMovement()->DisableMovement();
    SetLifeSpan(3.0f);

    if (Controller)
    {
        Controller->ChangeState(NAME_Spectating);
    }
}

void AJoyCharacter::OnHealthChanged(float Health)
{
    TextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}


