// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SlashCharacter.h"
#include "GameFramework/SpringArmComponent.h" 
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ASlashCharacter::ASlashCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	//ī�޶� ���� - �� - ��Ʈ�ѷ� ȸ�� ��ġ-��-�� �⺻�� ���� : ī�޶� ȸ�� ���� on/off
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 300.f;
	SpringArm->bUsePawnControlRotation = true;

	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera->SetupAttachment(SpringArm);

}

void ASlashCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(SlashContext, 0);
		}
	}
}

void ASlashCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//EnhancedInputComponent�� IA ����� �Լ� ���ε� �Լ�
void ASlashCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//EnhancedInputComponent�� nullptr���� Ȯ��
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//EnhancedInputComponent�� �Է�->���(�̵�) �Լ� ���ε�
		EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &ASlashCharacter::Move);

		//EnhancedInputComponent�� �Է�->���(ȸ��) �Լ� ���ε�
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASlashCharacter::Look);

		//EnhancedInputComponent�� Default ���� �Լ� ���ε�
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ASlashCharacter::Jump);
		
		//EnhancedInputComponent�� EKey �Է� �Լ� ���ε�
		EnhancedInputComponent->BindAction(EKeyAction, ETriggerEvent::Triggered, this, &ASlashCharacter::EKeyPressed);

		//EnhancedInputComponent�� ���� �Է� �Լ� ���ε�
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ASlashCharacter::Attack);

		//EnhancedInputComponent�� ȸ�� �Է� �Լ� ���ε�
		EnhancedInputComponent->BindAction(DodgeAction, ETriggerEvent::Triggered, this, &ASlashCharacter::Dodge);
	}
}

void ASlashCharacter::MoveForward(float Value)
{

}

//IA �̺�Ʈ ��� �Լ�
void ASlashCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	//��Ʈ�ѷ� ȸ�� Get �Լ� : Controller->GetControlRotation() : ���� ��Ʈ�ѷ��� ȸ�� Yaw Pitch Roll ������. Pawn ���� ��� ī�޶� ȸ�� ��� ����.
	const FRotator Rotation = Controller->GetControlRotation();

	//Z�� ȸ���� ������ ȸ�� ��ü ����, FRotator (Pitch, Yaw, Roll) !Vector�� �ƴ� Rotator
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	//Rotator -> RotationMatrix -> Vector ��ȯ���� 
	// 
	// < 3 Dimention Rotation Matrix in Unreal > 
	//  Xaxis : [CosP*CosY,  CosP*CosY,  SinP,  OriginX] : Front Vector 
	//  Yaxis :	[SinR*SinP*CosY - CosR*SinY,  SinR*SinP*SinY + CosR*CosY,  -SinR*CosP,  OriginY] : Right Vector 
	//  Zaxis : [-(CosR*SinP*CosY+SinR*SinY),  CosY*SinR - CosR*SinP*SinY,  CosR*CosP,  OriginZ] : Top Vector
	//  0     : [0,  0,  0,  1]
	// 
	//R[0, ��, 0] -> M[[CosPcosY, CosPSinY, ...]] -> V(M[0][0], M[0][1], M[0][2])
	const FVector ForwardDirrection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(ForwardDirrection, MovementVector.Y);  // W, S Key
	const FVector RightDirrection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(RightDirrection, MovementVector.X);  // A, D Key

}

void ASlashCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddControllerPitchInput(LookAxisVector.Y);
	AddControllerYawInput(LookAxisVector.X);
}

void ASlashCharacter::EKeyPressed(const FInputActionValue& Value)
{
}

void ASlashCharacter::Attack(const FInputActionValue& Value)
{
}

void ASlashCharacter::Dodge(const FInputActionValue& Value)
{
}
