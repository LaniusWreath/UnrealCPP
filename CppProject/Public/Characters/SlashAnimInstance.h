// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SlashAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class CPPPROJECT_API USlashAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	//Event Blueprint Initialize Animation (BeginPlay)
	virtual void NativeInitializeAnimation() override;
	//Event Blueprint Update Animation (Tick)
	virtual void NativeUpdateAnimation(float DeltaTime) override;

	//전방선언+변수생성 한번에 가능함
	UPROPERTY(BlueprintReadOnly)
	class ASlashCharacter* SlashCharacter;
	
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	class UCharacterMovementComponent* SlashCharacterMovement;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	float GroundSpeed;

	//
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	bool IsFalling;
};