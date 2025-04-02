// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterCharacter.h"
#include "Gun.h"
#include "Components/CapsuleComponent.h"
#include "KillEmAllGameMode.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);

	if(GunClasses.Num() >= 2)
	{
		GunHolders.Add(GetWorld()->SpawnActor<AGun>(GunClasses[0]));
		GunHolders.Add(GetWorld()->SpawnActor<AGun>(GunClasses[1]));

		GunHolders[0]->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("RifleSocket"));
		GunHolders[1]->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("LauncherSocket"));

		GunHolders[0]->SetOwner(this);
		GunHolders[1]->SetOwner(this);

		GunHolders[0]->SetActorHiddenInGame(false);
		GunHolders[1]->SetActorHiddenInGame(true);
		
		Gun = GunHolders[0];
	}
	Health = MaxHealth;
}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AShooterCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &AShooterCharacter::LookUp);
	PlayerInputComponent->BindAxis("LookRight", this, &AShooterCharacter::LookRight);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AShooterCharacter::Shoot);
	PlayerInputComponent->BindKey(EKeys::One, IE_Pressed, this, &AShooterCharacter::SwitchRifle);
	PlayerInputComponent->BindKey(EKeys::Two, IE_Pressed, this, &AShooterCharacter::SwitchLauncher);
}

float AShooterCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float DamageApplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	if (Health > 0) Health -= DamageApplied;
	UE_LOG(LogTemp, Warning, TEXT("Health left: %f"), Health);

	if(IsDead())
	{
		GetWorld()->GetAuthGameMode<AKillEmAllGameMode>()->PawnKilled(this);

		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	return DamageApplied;
}

void AShooterCharacter::SwitchRifle()
{
	if (CurrentGunType == 0) return;
	CurrentGunType = 0;
	
	GunHolders[0]->SetActorHiddenInGame(false);
	GunHolders[1]->SetActorHiddenInGame(true);

	Gun = GunHolders[0];
}

void AShooterCharacter::SwitchLauncher()
{
	if (CurrentGunType == 1) return;
	CurrentGunType = 1;
	
	GunHolders[0]->SetActorHiddenInGame(true);
	GunHolders[1]->SetActorHiddenInGame(false);

	Gun = GunHolders[1];
}

void AShooterCharacter::MoveForward(float AxisValue)
{
	// Move the character forward relative to its current rotation
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AShooterCharacter::MoveRight(float AxisValue)
{
	// Move the character right relative to its current rotation
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AShooterCharacter::LookUp(float AxisValue)
{
	// Rotate the character up and down
	AddControllerPitchInput(AxisValue);
}

void AShooterCharacter::LookRight(float AxisValue)
{
	// Rotate the character left and right
	AddControllerYawInput(AxisValue);
}

void AShooterCharacter::Shoot()
{
	Gun->PullTrigger();
}