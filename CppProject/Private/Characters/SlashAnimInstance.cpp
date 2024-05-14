// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/SlashAnimInstance.h"
#include "Characters/SlashCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void USlashAnimInstance::NativeInitializeAnimation()
{
	//Super : 서브클래스가 슈퍼클래스의 기능을 덮어씀. 서브 클래스 메서드 내부에서 Super::붙이면 부모 클래스의 해당 메서드를 호출할 수 있음.
	//UAnimInstance 클래스의 NativeInitializeAnimation() 원본 함수를 호출한다는 뜻.
	//부모 클래스의 메서드는 자식 클래스에서 독립적으로 실행되고, 재정의 되지 않음. 부모 클래스의 메서드 원본을 재정의 하지 않고 그대로 가져와 사용할 수 있다는 뜻.
	Super::NativeInitializeAnimation();

	//소유한 APawn 포인터 반환, ASlashCharacter로 형변환.
	SlashCharacter = Cast<ASlashCharacter>(TryGetPawnOwner());
	if (SlashCharacter)
	{
		//ASlashCharacter의 CharacterMovementComponent 가져옴(CharacterMovementComponent는 ACharacter클래스에 preattached이기 때문에 헤더만 추가된다면 객체 선언 없이 바로 포인팅/메서드 호출 할 수 있음.
		SlashCharacterMovement = SlashCharacter->GetCharacterMovement();
	}
}

void USlashAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (SlashCharacterMovement)
	{
		//
		//KismetMathLibrary(클래스)에서 메서드 호출하는 방식. 정적인 메서드(클래스의 상태나 변수를 Set하지 않음)만 갖기 때문에 객체를 만들 필요 X.
		GroundSpeed = UKismetMathLibrary::VSizeXY(SlashCharacterMovement->Velocity);
		IsFalling = SlashCharacterMovement->IsFalling();
	}
}
