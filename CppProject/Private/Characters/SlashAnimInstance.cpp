// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/SlashAnimInstance.h"
#include "Characters/SlashCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void USlashAnimInstance::NativeInitializeAnimation()
{
	//Super : ����Ŭ������ ����Ŭ������ ����� ���. ���� Ŭ���� �޼��� ���ο��� Super::���̸� �θ� Ŭ������ �ش� �޼��带 ȣ���� �� ����.
	//UAnimInstance Ŭ������ NativeInitializeAnimation() ���� �Լ��� ȣ���Ѵٴ� ��.
	//�θ� Ŭ������ �޼���� �ڽ� Ŭ�������� ���������� ����ǰ�, ������ ���� ����. �θ� Ŭ������ �޼��� ������ ������ ���� �ʰ� �״�� ������ ����� �� �ִٴ� ��.
	Super::NativeInitializeAnimation();

	//������ APawn ������ ��ȯ, ASlashCharacter�� ����ȯ.
	SlashCharacter = Cast<ASlashCharacter>(TryGetPawnOwner());
	if (SlashCharacter)
	{
		//ASlashCharacter�� CharacterMovementComponent ������(CharacterMovementComponent�� ACharacterŬ������ preattached�̱� ������ ����� �߰��ȴٸ� ��ü ���� ���� �ٷ� ������/�޼��� ȣ�� �� �� ����.
		SlashCharacterMovement = SlashCharacter->GetCharacterMovement();
	}
}

void USlashAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (SlashCharacterMovement)
	{
		//
		//KismetMathLibrary(Ŭ����)���� �޼��� ȣ���ϴ� ���. ������ �޼���(Ŭ������ ���³� ������ Set���� ����)�� ���� ������ ��ü�� ���� �ʿ� X.
		GroundSpeed = UKismetMathLibrary::VSizeXY(SlashCharacterMovement->Velocity);
		IsFalling = SlashCharacterMovement->IsFalling();
	}
}
