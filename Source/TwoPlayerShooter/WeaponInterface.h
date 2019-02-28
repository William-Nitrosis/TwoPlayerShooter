// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../CoreUObject/Public/UObject/Interface.h"
#include "Engine.h"
#include "WeaponInterface.generated.h"

UINTERFACE(BlueprintType)
class TWOPLAYERSHOOTER_API UWeaponInterface : public UInterface
{
	GENERATED_BODY()
};

class TWOPLAYERSHOOTER_API IWeaponInterface
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "MyCategory")
		void AttackStart();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "MyCategory")
		void AttackEnd();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "MyCategory")
		void Reload();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "MyCategory")
		void ScopeIn();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "MyCategory")
		void ScopeOut();
};