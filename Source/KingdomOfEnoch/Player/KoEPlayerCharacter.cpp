// Fill out your copyright notice in the Description page of Project Settings.

#include "KoEPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../Interfaces/KoEInteractable.h"
#include "Components/CapsuleComponent.h" 

AKoEPlayerCharacter::AKoEPlayerCharacter()
{
    bReplicates = true;
    SetReplicateMovement(true);

    // Player-specific movement/orientation
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.f, 720.f, 0.f);

    // Camera boom
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 1200.f;     // high/top-down
    CameraBoom->bDoCollisionTest = false;
    CameraBoom->SetUsingAbsoluteRotation(true);
    CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f)); // tilt down

    // Top-down camera
    TopDownCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
    TopDownCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    TopDownCamera->bUsePawnControlRotation = false;
}


void AKoEPlayerCharacter::TryInteract()
{
    // Start a little above the feet
    const float HalfHeight = GetCapsuleComponent() ? GetCapsuleComponent()->GetScaledCapsuleHalfHeight() : 88.f;
    const FVector Start = GetActorLocation() + FVector(0, 0, HalfHeight * 0.5f);

    // Use controller yaw (flattened) so it works on server too
    FRotator ViewRot = GetControlRotation();
    ViewRot.Pitch = 0.f; ViewRot.Roll = 0.f;
    FVector Dir = ViewRot.Vector();
    if (!Dir.IsNearlyZero())
    {
        Dir.Z = 0.f; Dir.Normalize();
    }
    else
    {
        Dir = GetActorForwardVector().GetSafeNormal2D();
    }

    const FVector End = Start + Dir * InteractDistance;

    FHitResult Hit;
    FCollisionQueryParams Params(SCENE_QUERY_STAT(KoEInteract), /*bTraceComplex*/ false, this);

    // Sphere sweep is more forgiving for top-down
    const FCollisionShape Shape = FCollisionShape::MakeSphere(InteractRadius);
    const bool bHit = GetWorld()->SweepSingleByChannel(
        Hit, Start, End, FQuat::Identity,
        /* TraceChannel */ ECC_Visibility, Shape, Params);

    if (!bHit) return;

    UObject* Target = nullptr;
    AActor* HitActor = Hit.GetActor();

    // Actor implements interface?
    if (HitActor && HitActor->GetClass()->ImplementsInterface(UKoEInteractable::StaticClass()))
    {
        Target = HitActor;
    }
    else if (HitActor)
    {
        // Look for any component that implements the interface
        const TSet<UActorComponent*>& Comps = HitActor->GetComponents();
        for (UActorComponent* C : Comps)
        {
            if (C && C->GetClass()->ImplementsInterface(UKoEInteractable::StaticClass()))
            {
                Target = C;
                break;
            }
        }
    }

    if (Target && IKoEInteractable::Execute_CanInteract(Target, this))
    {
        IKoEInteractable::Execute_Interact(Target, this);
    }
}

void AKoEPlayerCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void AKoEPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}