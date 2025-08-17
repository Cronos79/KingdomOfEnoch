// Fill out your copyright notice in the Description page of Project Settings.


#include "KoEPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "UObject/ConstructorHelpers.h"
#include "KoEPlayerCharacter.h"

AKoEPlayerController::AKoEPlayerController()
{
    // Load your assets from /Game/Input/
    static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMCObj(TEXT("/Game/Input/KoEInputMappingContext.KoEInputMappingContext"));
    static ConstructorHelpers::FObjectFinder<UInputAction> MFObj(TEXT("/Game/Input/KoEMoveIA.KoEMoveIA"));
    static ConstructorHelpers::FObjectFinder<UInputAction> IntObj(TEXT("/Game/Input/KoEInteractIA.KoEInteractIA"));

    IMC_Default = IMCObj.Succeeded() ? IMCObj.Object : nullptr;
    IA_Move = MFObj.Succeeded() ? MFObj.Object : nullptr;
    IA_Interact = IntObj.Succeeded() ? IntObj.Object : nullptr;	
}

void AKoEPlayerController::BeginPlay()
{
    Super::BeginPlay();
    if (ULocalPlayer* LP = GetLocalPlayer())
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
        {
            Subsystem->AddMappingContext(IMC_Default, /*Priority*/0);
        }
    }
}

void AKoEPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(InputComponent))
    {
        if (IA_Move)
        {
            EIC->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AKoEPlayerController::Input_Move2D);
            EIC->BindAction(IA_Move, ETriggerEvent::Completed, this, &AKoEPlayerController::Input_Move2D);
        }
        if (IA_Interact)
        {
            EIC->BindAction(IA_Interact, ETriggerEvent::Started, this, &AKoEPlayerController::Input_Interact);
        }
    }
}

void AKoEPlayerController::Input_Move2D(const FInputActionValue& V)
{
    if (APawn* P = GetPawn())
    {
        const FVector2D M = V.Get<FVector2D>();
        // If your camera can rotate, use controller yaw so movement is camera-relative:
        const FRotator Yaw(0.f, GetControlRotation().Yaw, 0.f);
        const FVector Forward = FRotationMatrix(Yaw).GetUnitAxis(EAxis::X);
        const FVector Right = FRotationMatrix(Yaw).GetUnitAxis(EAxis::Y);

        P->AddMovementInput(Forward, M.Y); // W/S
        P->AddMovementInput(Right, M.X); // A/D

        UE_LOG(LogTemp, Log, TEXT("Move2D: X=%.2f Y=%.2f"), M.X, M.Y);
    }
}

void AKoEPlayerController::Input_Interact()
{
    ServerTryInteract();
    // (optional) Predict locally: 
    if (AKoEPlayerCharacter* C = GetPawn<AKoEPlayerCharacter>()) C->TryInteract();
}

void AKoEPlayerController::ServerTryInteract_Implementation()
{
    if (AKoEPlayerCharacter* C = GetPawn<AKoEPlayerCharacter>())
    {
        C->TryInteract();         // runs on the server
    }
}
