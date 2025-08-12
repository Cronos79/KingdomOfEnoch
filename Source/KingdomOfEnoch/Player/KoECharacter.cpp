// Fill out your copyright notice in the Description page of Project Settings.


#include "KoECharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AKoECharacter::AKoECharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    bReplicates = true;
    SetReplicateMovement(true);

    CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 1200.f;     // high/top-down
    CameraBoom->bDoCollisionTest = false;
    CameraBoom->SetUsingAbsoluteRotation(true);
    CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f)); // tilt down

    TopDownCamera = CreateDefaultSubobject<UCameraComponent>("TopDownCamera");
    TopDownCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    TopDownCamera->bUsePawnControlRotation = false;

    // Movement feels better with orient-to-movement for top-down
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.f, 720.f, 0.f);

    HealthComp = CreateDefaultSubobject<UKoEHealthComponent>("HealthComp");
}

// Called when the game starts or when spawned
void AKoECharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKoECharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AKoECharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

