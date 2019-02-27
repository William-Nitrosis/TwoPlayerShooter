// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// == Add components 
	// = Camera
	// Create camera in world from pointer
	FP_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("FP_Camera"));
	// Attach to the root of object
	FP_Camera->SetupAttachment(RootComponent);
	// Set location of camera
	FP_Camera->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-0.0f, 0.0f, 0.0f));

	// = Arm mesh
	// Create skel mesh from pointer
	FP_Arms = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Arms"));
	// Attach to camera
	FP_Arms->AttachToComponent(FP_Camera, FP_ArmsRules);
	// Set arm location
	FP_Arms->SetRelativeLocationAndRotation(FVector(0.0f, -4.0f, -158.0f), FRotator(-0.0f, 0.0f, 0.0f));
	// Make sure only the player can see
	FP_Arms->bOnlyOwnerSee = true;
	// Set shadow settings
	FP_Arms->CastShadow = false;
	
	// == Child actor comps
	// Create weapon 1 in world from pointer
	WeaponSlot1 = CreateDefaultSubobject<UChildActorComponent>(TEXT("WeaponSlot1"));
	// Attach to camera
	WeaponSlot1->AttachToComponent(FP_Arms, FAttachmentTransformRules::SnapToTargetIncludingScale, FName("hand_r_Weapon"));




	// == Camera settings
	FP_Camera->bUsePawnControlRotation = true;
	FP_Camera->FieldOfView = UserSetting_FOV;

	// motion cancer
	FP_Camera->PostProcessSettings.bOverride_MotionBlurAmount = true;
	FP_Camera->PostProcessSettings.bOverride_MotionBlurMax = true;
	FP_Camera->PostProcessSettings.bOverride_MotionBlurPerObjectSize = true;
	FP_Camera->PostProcessSettings.MotionBlurAmount = 0.f;
	FP_Camera->PostProcessSettings.bOverride_MotionBlurMax = 0.f;
	FP_Camera->PostProcessSettings.MotionBlurPerObjectSize = 0.f;

	// Take control of the default Player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind inputs to functions
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveSide", this, &APlayerCharacter::MoveSide);

	PlayerInputComponent->BindAxis("MouseX", this, &APlayerCharacter::MouseX);
	PlayerInputComponent->BindAxis("MouseY", this, &APlayerCharacter::MouseY);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::PlayerJump);

	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &APlayerCharacter::ShootDown);
	PlayerInputComponent->BindAction("Shoot", IE_Released, this, &APlayerCharacter::ShootUp);

	PlayerInputComponent->BindAction("AimingDownSights", IE_Pressed, this, &APlayerCharacter::ADSDown);
	PlayerInputComponent->BindAction("AimingDownSights", IE_Released, this, &APlayerCharacter::ADSUp);


}

// ====================
// Input functions
// ====================

// == Movement inputs
void APlayerCharacter::MoveForward(float AxisValue)
{
	MovementInput.X = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
	this->AddMovementInput(this->GetActorForwardVector(), MovementInput.X, false);
}

void APlayerCharacter::MoveSide(float AxisValue)
{
	MovementInput.Y = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
	this->AddMovementInput(this->GetActorRightVector(), MovementInput.Y, false);
}

// == Mouse inputs
void APlayerCharacter::MouseX(float AxisValue)
{
	this->AddControllerYawInput(AxisValue * UserSetting_MouseSensitivity);
}

void APlayerCharacter::MouseY(float AxisValue)
{
	if (UserSetting_InvertYAxis)
	{
		AxisValue *= -1.f;
	} 
	this->AddControllerPitchInput(AxisValue * UserSetting_MouseSensitivity);
}

// == Jump
void APlayerCharacter::PlayerJump()
{
	this->Jump(); 
}

// == Shooting
void APlayerCharacter::ShootDown()
{

}

void APlayerCharacter::ShootUp()
{

}

// == Aiming
void APlayerCharacter::ADSDown()
{
	GetCharacterMovement()->MaxWalkSpeed = 350;
	
}

void APlayerCharacter::ADSUp()
{
	GetCharacterMovement()->MaxWalkSpeed = 600;
	
}