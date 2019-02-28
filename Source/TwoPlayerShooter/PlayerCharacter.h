// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/ChildActorComponent.h"
#include "WeaponInterface.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class TWOPLAYERSHOOTER_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// == Add components 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCameraComponent* FP_Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USkeletalMeshComponent* FP_Arms;
	FAttachmentTransformRules FP_ArmsRules = FAttachmentTransformRules::KeepRelativeTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UChildActorComponent* WeaponSlot1;

	// == Input functions
	// axis
	void MoveForward(float AxisValue);
	void MoveSide(float AxisValue);
	void MouseWheel(float inputValue);
	void MouseX(float inputValue);
	void MouseY(float inputValue);

	// actions
	void PlayerJump();
	void ShootDown();
	void ShootUp();
	void ADSDown();
	void ADSUp();
	void Reload();

	// == Input variables
	FVector2D MovementInput;

	// == Weapon system variables
	bool Shooting = false;
	bool CanShoot = false;

	// == User settings
	float UserSetting_MouseSensitivity = 0.5f;
	bool UserSetting_InvertYAxis = false;
	float UserSetting_FOV = 105.f;

};
